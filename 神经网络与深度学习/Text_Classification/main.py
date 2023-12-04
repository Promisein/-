import torch
import torch.nn as nn
import torchtext
from torchtext.datasets import AG_NEWS
import os
from collections import Counter, OrderedDict
import myModel

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# 下载数据集, 并且观察数据形式
path = r'./data/datasets/AG_NEWS/'
os.makedirs('data', exist_ok=True)
train_dataset, test_dataset = AG_NEWS(root='./data', split=('train', 'test'))
classes = ['World', 'Sports', 'Business', 'Sci/Tech']

for i, x in zip(range(5), train_dataset):
    print(f"**{classes[x[0] - 1]}** -> {x[1]}\n")

train_dataset = list(train_dataset)
test_dataset = list(test_dataset)

# 使用dataloader读取给定的数据集
# 英语分词器
tokenizer = torchtext.data.utils.get_tokenizer('basic_english')


counter = Counter()
for (label, line) in train_dataset:
    counter.update(tokenizer(line))
# 将计数器中的项按照单词出现的次数进行降序排序，然后创建一个有序字典。
order_dict = OrderedDict(sorted(counter.items(), key=lambda x: x[1], reverse=True))
# 构建以word-indice为键值对的词表
vocab = torchtext.vocab.vocab(order_dict, min_freq=1)
vocab_size = len(vocab)
print(vocab_size)


# 填充句子为最大长度
def padify(b):
    # b is the list of tuples of length batch_size
    #   - first element of a tuple = label,
    #   - second = feature (text sequence)
    # build vectorized sequence
    v = [vocab.lookup_indices(tokenizer(x[1])) for x in b]
    # first, compute max length of a sequence in this minibatch
    l = max(map(len, v))
    return (  # tuple of two tensors - labels and features
        torch.LongTensor([t[0] - 1 for t in b]),
        torch.stack([torch.nn.functional.pad(torch.tensor(t), (0, l - len(t)), mode='constant', value=0) for t in v]))


train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=16, collate_fn=padify, shuffle=True)
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=16, collate_fn=padify, shuffle=True)


# def train_epoch(net, dataloader, lr, optimizer=None, loss_fn=None, epoch_size=None, report_freq=200):
#     optimizer = optimizer or torch.optim.Adam(net.parameters(), lr=lr)
#     loss_fn = loss_fn or nn.CrossEntropyLoss()
#     net.train()  # 训练模式
#     total_loss, acc, count, i = 0, 0, 0, 0
#     for labels, features in dataloader:
#         optimizer.zero_grad()
#         out = net(features)
#         loss = loss_fn(out, labels)  # cross_entropy(out,labels),交叉熵函数自带了softmax运算
#         loss.backward()
#         optimizer.step()
#         total_loss += loss
#         predicted = torch.argmax(out, 1)  # 1指每一列的最大值
#         acc += (predicted == labels).sum()
#         count += len(labels)
#         i += 1
#         if i % report_freq == 0:
#             print(f"{count}: acc={acc.item() / count}")
#         if epoch_size and count > epoch_size:
#             break
#     print(f'loss is {total_loss.item() / count}')
#     print(f'accuracy is {acc.item() / count * 100}%')


Losses = []
Accuracies = []


def train_epoch(model, train_loader, lr, epoch_size=None, model_name=None):
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=lr, weight_decay=5e-4)
    single_loss = []
    single_accuracy = []
    for epoch in range(epoch_size):
        model.train()
        total_loss = 0

        for labels, inputs in train_loader:
            inputs, labels = inputs.to(device), labels.to(device)
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()

            total_loss += loss.item()

        average_loss = total_loss / len(train_loader)

        model.eval()
        correct = 0
        total = 0

        with torch.no_grad():
            for labels, inputs in train_loader:
                inputs, labels = inputs.to(device), labels.to(device)
                outputs = model(inputs)
                _, predicted = torch.max(outputs.data, 1)
                total += labels.size(0)
                correct += (predicted == labels).sum().item()

        accuracy = correct / total

        single_loss.append(average_loss)
        single_accuracy.append(accuracy)
        print(f'Epoch [{epoch + 1}/{epoch_size}], Loss: {average_loss:.4f}, Validation Accuracy: {accuracy:.2%}, '
              f'model name: {model_name}')

    Losses.append(single_loss)
    Accuracies.append(single_accuracy)


epoch_size = 2
lr = 0.001
model = myModel.EmbedClassifier(vocab_size, embed_dim=32, hidden_dim=64, num_class=len(classes))
model.to(device)
train_epoch(model, train_loader, lr=0.001, epoch_size=epoch_size, model_name="EmbedClassifier")

model = myModel.RNNTextClassifier(vocab_size, 64, 128, len(classes))
model.to(device)
train_epoch(model, train_loader, lr=lr, epoch_size=epoch_size, model_name="RNNTextClassifier")

num_filters = 100  # 卷积核数量
filter_sizes = [3, 4, 5]  # 卷积核大小列表
model = myModel.CNNTextClassifier(vocab_size, 32, num_filters, filter_sizes=filter_sizes, num_class=len(classes))
model.to(device)
train_epoch(model, train_loader, lr=lr, epoch_size=epoch_size, model_name="CNNTextClassifier")

hidden_dim = 256  # Transformer隐藏层维度
num_heads = 8  # 多头注意力头数
num_layers = 4  # Transformer层数
model = myModel.TransformerClassifier(vocab_size, embed_dim=32, hidden_dim=hidden_dim, num_heads=num_heads,
                                      num_layers=num_layers,
                                      num_class=len(classes))
model.to(device)
train_epoch(model, train_loader, lr=lr, epoch_size=epoch_size, model_name="TransformerTextClassifier")




