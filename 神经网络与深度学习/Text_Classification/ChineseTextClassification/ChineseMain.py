import pandas as pd
import jieba as jb
from torch.utils.data import DataLoader
import re
import torch
import torch.nn as nn
import myModel
from torchtext.data.utils import get_tokenizer
from torchtext.vocab import build_vocab_from_iterator
import time
from torchtext.data.functional import to_map_style_dataset
import matplotlib.pyplot as plt
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

df_train = pd.read_csv(r'./data/test_data.csv')
df_test = pd.read_csv(r'./data/test_data.csv')
# df = pd.read_csv(r'./data/small.csv')

moods = {0: '喜悦', 1: '愤怒', 2: '厌恶', 3: '低落'}


# 定义删除除字母,数字，汉字以外的所有符号的函数
def remove_punctuation(line):
    line = str(line)
    if line.strip() == '':
        return ''
    rule = re.compile(u"[^a-zA-Z0-9\u4E00-\u9FA5]")
    line = rule.sub('', line)
    return line


def stopwordslist(filepath):
    stopwords = [line.strip() for line in open(filepath, 'r', encoding='utf-8').readlines()]
    return stopwords


# 加载停用词
stopwords = stopwordslist("data/cn_stopwords.txt")
df_train['clean_review'] = df_train['review'].apply(remove_punctuation)
df_test['clean_review'] = df_test['review'].apply(remove_punctuation)
print(df_train.sample(10))

df_train['cut_review'] = df_train['clean_review'].apply(
    lambda x: " ".join([w for w in list(jb.cut(x)) if w not in stopwords]))
df_test['cut_review'] = df_test['clean_review'].apply(
    lambda x: " ".join([w for w in list(jb.cut(x)) if w not in stopwords]))
print(df_train.head())

# 使用空格分词器
tokenizer = get_tokenizer('basic_english')

# 迭代器是一次性用品
train_iter = iter(df_train[['cut_review', 'label']].values)


def yield_tokens(data_iter):
    for text, _ in data_iter:
        yield tokenizer(text)


vocab = build_vocab_from_iterator(yield_tokens(train_iter), specials=["<unk>"])
vocab.set_default_index(vocab["<unk>"])  # 设置默认索引，如果找不到单词，则会选择默认索引

print(vocab(['不錯', '妳', '別', '圓圓', '拖下水', '明明', '暧昧', '刚才', '说', '何韵诗', '爱', '听', '阿诗', '今天',
             '玩儿']))

label_name = list(set(df_train['label'].values))
print(label_name)

text_pipeline = lambda x: vocab(tokenizer(x))
label_pipeline = lambda x: label_name.index(x)

print(text_pipeline('甜蜜 时间 会 亲亲 最近 工作 太忙 白天 晚上 没有 时间 已经 很久没 某人'))
print(label_pipeline(3))


def collate_batch(batch):
    label_list, text_list, offsets = [], [], [0]

    for (_text, _label) in batch:
        # 标签列表
        label_list.append(label_pipeline(_label))

        # 文本列表
        processed_text = torch.tensor(text_pipeline(_text), dtype=torch.int64)
        text_list.append(processed_text)

        # 偏移量，即语句的总词汇量
        offsets.append(processed_text.size(0))

    label_list = torch.tensor(label_list, dtype=torch.int64)
    text_list = torch.cat(text_list)
    offsets = torch.tensor(offsets[:-1]).cumsum(dim=0)  # 返回维度dim中输入元素的累计和

    return text_list.to(device), label_list.to(device), offsets.to(device)


EPOCHS = 10  # epoch
LR = 0.001  # 学习率
BATCH_SIZE = 64  # batch size for training

# 构建数据集
train_iter = iter(df_train[['cut_review', 'label']].values)
test_iter = iter(df_test[['cut_review', 'label']].values)
train_dataset = to_map_style_dataset(train_iter)
test_dataset = to_map_style_dataset(test_iter)

train_dataloader = DataLoader(train_dataset, batch_size=BATCH_SIZE,
                              shuffle=True, collate_fn=collate_batch)

valid_dataloader = DataLoader(test_dataset, batch_size=BATCH_SIZE,
                              shuffle=True, collate_fn=collate_batch)


def train(dataloader):
    model.train()  # 切换为训练模式
    total_acc, train_loss, total_count = 0, 0, 0
    log_interval = 1000
    start_time = time.time()

    for idx, (text, label, offsets) in enumerate(dataloader):
        predicted_label = model(text, offsets)
        # predicted_label = model(text)
        optimizer.zero_grad()  # grad属性归零
        loss = criterion(predicted_label, label)  # 计算网络输出和真实值之间的差距，label为真实值
        loss.backward()  # 反向传播
        torch.nn.utils.clip_grad_norm_(model.parameters(), 0.1)  # 梯度裁剪
        optimizer.step()  # 每一步自动更新

        # 记录acc与loss
        total_acc += (predicted_label.argmax(1) == label).sum().item()
        train_loss += loss.item()
        total_count += label.size(0)

        if idx % log_interval == 0 and idx > 0:
            elapsed = time.time() - start_time
            print('| epoch {:1d} | {:4d}/{:4d} batches '
                  '| train_acc {:4.3f} train_loss {:4.5f}'.format(epoch, idx, len(dataloader),
                                                                  total_acc / total_count, train_loss / total_count))
            total_acc, train_loss, total_count = 0, 0, 0
            start_time = time.time()


def evaluate(dataloader):
    model.eval()  # 切换为测试模式
    total_acc, train_loss, total_count = 0, 0, 0

    with torch.no_grad():
        for idx, (text, label, offsets) in enumerate(dataloader):
            predicted_label = model(text, offsets)

            loss = criterion(predicted_label, label)  # 计算loss值
            # 记录测试数据
            total_acc += (predicted_label.argmax(1) == label).sum().item()
            train_loss += loss.item()
            total_count += label.size(0)

    return total_acc / total_count, train_loss / total_count


num_class = len(label_name)
vocab_size = len(vocab)
em_size = 64
hidden_dim = 128
filter_sizes = [3, 4, 5]  # 卷积核大小列表
num_filters = 100
# model = myModel.TextClassificationModel(vocab_size, em_size, num_class).to(device)
# model = myModel.LSTMClassificationModel(vocab_size, em_size, hidden_dim, num_class).to(device)
# model = myModel.RNNTextClassifier(vocab_size, em_size, hidden_dim, num_class).to(device)
# model = myModel.CNNTextClassifier(vocab_size, em_size, filter_sizes, num_filters, num_class).to(device)
# model = myModel.TransformerClassifier(vocab_size, em_size, 8, 4, num_class).to(device)

model_name = ['FC', 'LSTM', 'RNN', 'CNN', 'Transformer']
model_list = [myModel.TextClassificationModel(vocab_size, em_size, num_class).to(device),
              myModel.LSTMClassificationModel(vocab_size, em_size, hidden_dim, num_class).to(device),
              myModel.RNNTextClassifier(vocab_size, em_size, hidden_dim, num_class).to(device),
              myModel.CNNTextClassifier(vocab_size, em_size, filter_sizes, num_filters, num_class).to(device),
              myModel.TransformerClassifier(vocab_size, em_size, 8, 4, num_class).to(device)]


model_index = 0
fig = plt.figure(figsize=(10, 12))
ax1 = fig.add_subplot(2, 1, 1)
ax2 = fig.add_subplot(2, 1, 2)
All_Loss = []
All_Acc = []
for model in model_list:
    Losses = []
    Acc = []
    criterion = torch.nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=LR)
    scheduler = torch.optim.lr_scheduler.StepLR(optimizer, 1.0, gamma=0.1)
    total_accu = None

    for epoch in range(1, EPOCHS + 1):
        epoch_start_time = time.time()
        train(train_dataloader)
        val_acc, val_loss = evaluate(valid_dataloader)

        # 获取当前的学习率
        lr = optimizer.state_dict()['param_groups'][0]['lr']

        if total_accu is not None and total_accu > val_acc:
            scheduler.step()
        else:
            total_accu = val_acc
        print('-' * 69)
        print('| epoch {:1d} | time: {:4.2f}s | '
              'valid_acc {:4.3f} valid_loss {:4.3f} '
              '| lr {:4.6f},  model_name = {}'.format(epoch,
                                                      time.time() - epoch_start_time,
                                                      val_acc, val_loss, lr,
                                                      model_name[model_index]))
        print('-' * 69)
        Losses.append(val_loss)
        Acc.append(val_acc)
    All_Loss.append(Losses)
    All_Acc.append(Acc)

for Losses, Acc in zip(All_Loss, All_Acc):
    ax1.plot(range(1, EPOCHS + 1), Losses, label=model_name[model_index])
    ax1.legend()
    ax2.plot(range(1, EPOCHS + 1), Acc, label=model_name[model_index])
    ax2.legend()
    model_index += 1

ax1.set_title("Loss in different model")
ax1.set_xlabel('epoch')
ax1.set_ylabel('loss')

ax2.set_title("Acc in different model")
ax2.set_xlabel('epoch')
ax2.set_ylabel('accuracy')
plt.show()


def predict(text, text_pipeline):
    with torch.no_grad():
        text = torch.tensor(text_pipeline(text))
        output = model(text, torch.tensor([0]))
        return output.argmax(1).item()


model = model.to("cpu")
# 喜悦
# 愤怒
# 厌恶
# 低落
ex_text_str = ['无论发生什么，我都感到喜悦洋溢，仿佛世界都变得明亮起来。',
               '我感到愤怒和愤慨，因为我受到了不公正的对待，我决心要为正义而战。',
               '每当我想起那个令人厌恶的经历，我都会感到恶心和厌烦，希望能忘记它。',
               '心情低落，仿佛一片灰暗笼罩了我的世界，我需要寻找力量来重新振作起来']

for single_text in ex_text_str:
    # ex_text_str = input("输入评价的文本:  ")
    print(single_text)
    single_text = remove_punctuation(single_text)
    single_text = jb.cut(single_text)
    clean_text = ""
    for word in single_text:
        if word not in stopwords:
            clean_text += word
            clean_text += " "

    print("该文本的类别是：%s" % moods[label_name[predict(clean_text, text_pipeline)]])
