from jittor.dataset.mnist import  MNIST
import jittor.transform as trans
from model import Model
from jittor import nn
from matplotlib import pyplot as pl
import numpy as np
# def train(model, train_loader, loss_function, optimizer, epoch):
#     model.train()
#     train_losses = list()
#     for batch_idx, (inputs, targets) in enumerate(train_loader):
#         outputs = model(inputs)
#         loss = loss_function(outputs, targets)
#         optimizer.step(loss)
#         train_losses.append(loss)
#
#         if batch_idx % 10 == 0:
#             print('Train Epoch: {} [{}/] ((:.f)%)]\tLoss: {:.6f)'
#                   .format(epoch, batch_idx, len(train_loader),
#                           100. * batch_idx / len(train_loader), loss.data[0]))
#     return train_losses
def test(model, val_loader, epoch):
    model.eval()
    test_loss = 0
    correct = 0
    total_acc = 0
    total_num = 0
    for batch_idx, (inputs, targets) in enumerate(val_loader):
        batch_size = inputs.shape[0]
        outputs = model(inputs)
        pred = np.argmax(outputs.data, axis=1)
        acc = np.sum(targets.data==pred)
        total_acc += acc
        total_num += batch_size
        acc = acc / batch_size
        print('Test Epoch: {} [{}/{} ({:.0f}%)]\tAcc: {:.6f}'.format(
            epoch, batch_idx, len(val_loader),
            100. * float(batch_idx) / len(val_loader), acc))
    print ('Total test acc =', total_acc / total_num)


def train(model, train_loader, optimizer, epoch, losses, losses_idx):
    model.train()
    lens = len(train_loader)
    for batch_idx, (inputs, targets) in enumerate(train_loader):
        outputs = model(inputs)
        loss = nn.cross_entropy_loss(outputs, targets)
        optimizer.step (loss)
        losses.append(loss.data[0])
        losses_idx.append(epoch * lens + batch_idx)
        if batch_idx % 10 == 0:
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                    epoch, batch_idx, len(train_loader),
                    100. * batch_idx / len(train_loader), loss.data[0]))


def main():
    batch_size = 64
    train_loader = MNIST(train=True, transform=trans.Resize(28)).set_attrs(batch_size=batch_size, shuffle=True)
    val_loader = MNIST(train=False, transform=trans.Resize(28)).set_attrs(batch_size=1, shuffle=False)

    learning_rate = 0.1
    momentum = 0.9
    weight_decay = 1e-4
    model = Model()
    optimizer = nn.SGD(model.parameters(), learning_rate, momentum, weight_decay)

    epochs = 5
    losses = []
    losses_idx = []
    for epoch in range(epochs):
        train(model, train_loader, optimizer, epoch, losses, losses_idx)
        test(model, val_loader, epoch)

    pl.plot(losses_idx, losses)
    pl.xlabel('Iterations')
    pl.ylabel('Train_loss')
    pl.show()

    model_path = '/home/jianing/PycharmProjects/pythonProject/mnist_model.pkl'
    model.save(model_path)

if __name__ == '__main__':
    main()
