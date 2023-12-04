import torchvision.datasets as dsets
import torchvision.transforms as transforms
import torch
import torch.nn as nn

train_data = dsets.MNIST(root='./data', train=True,
                         transform=transforms.ToTensor(), download=True)

test_data = dsets.MNIST(root='./data', train=False,
                        transform=transforms.ToTensor())

batch_size = 64
train_gen = torch.utils.data.DataLoader(dataset=train_data,
                                        batch_size=batch_size,
                                        shuffle=True)

test_gen = torch.utils.data.DataLoader(dataset=test_data,
                                       batch_size=batch_size,
                                       shuffle=False)

print(train_gen)


class LeNet(nn.Module):
    def __init__(self):
        super(LeNet, self).__init__()
        self.conv1 = nn.Sequential(  # input_size=(1*28*28)
            nn.Conv2d(1, 6, 5, 1, 2),  # padding=2保证输入输出尺寸相同
            nn.ReLU(),  # input_size=(6*28*28)
            nn.MaxPool2d(kernel_size=2, stride=2),  # output_size=(6*14*14)
        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(6, 16, 5),
            nn.ReLU(),  # input_size=(16*10*10)
            nn.MaxPool2d(2, 2)  # output_size=(16*5*5)
        )
        self.fc1 = nn.Sequential(
            nn.Linear(16 * 5 * 5, 120),
            nn.ReLU()
        )
        self.fc2 = nn.Sequential(
            nn.Linear(120, 84),
            nn.ReLU()
        )
        self.fc3 = nn.Linear(84, 10)

    # 定义前向传播过程，输入为x
    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        # print(x)
        x = x.view(x.size()[0], -1)
        # print(x)
        x = self.fc1(x)
        x = self.fc2(x)
        x = self.fc3(x)
        return x


net = LeNet()
device = 'cpu'
if torch.cuda.is_available():
    net.cuda()
    device = 'cuda:0'

loss_function = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(net.parameters(), lr=0.01)

net.train()
losses = []
epochs = []


for epoch in range(5):
    sum_loss = 0.0
    for i, data in enumerate(train_gen):
        inputs, labels = data
        inputs, labels = inputs.to(device), labels.to(device)

        # 梯度清零
        optimizer.zero_grad()

        # forward + backward
        outputs = net(inputs)
        loss = loss_function(outputs, labels)
        loss.backward()
        optimizer.step()

        # 每训练100个batch打印一次平均loss
        sum_loss += loss.item()
        if i % 100 == 99:
            print('[%d, %d] loss: %.03f'
                  % (epoch + 1, i + 1, sum_loss / 100))

            sum_loss = 0.0

            # 每跑完一次epoch测试一下准确率
    with torch.no_grad():
        correct = 0
        total = 0
        for data in test_gen:
            images, labels = data
            images, labels = images.to(device), labels.to(device)
            outputs = net(images)
            # print(outputs.shape)

            # 取得分最高的那个类
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum()
        print('第%d个epoch的识别准确率为：%d%%' % (epoch + 1, (100 * torch.true_divide(correct, total))))










