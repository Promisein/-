import torch
import matplotlib.pyplot as plt

# 构造一些线性分布的数据
def generate_data(nums_data=50):
    x = torch.linspace(0, 1, nums_data)
    x = torch.unsqueeze(x, dim=1)
    k = 2
    y = k * x + torch.rand(x.size())
    data = {"x": x, "y": y}
    return data

def plotdata(x, y, model):
    pred_1 = model(x).detach().numpy()
    plt.scatter(x, y, c=x)
    plt.plot(x, pred_1, "r-", label="LinearRegression")
    plt.title("Scatter plot with Linear Regression")
    plt.legend()
    plt.show()


class LinearRegressionModel(torch.nn.Module):
    def __init__(self):
        super(LinearRegressionModel, self).__init__()
        self.linear = torch.nn.Linear(1, 1)  # One in and one out

    def forward(self, x):
        y_pred = self.linear(x)
        return y_pred


if __name__ == '__main__':
    # 构造数据
    data = generate_data()
    print(data)

    # 初始化模型
    model = LinearRegressionModel()
    plotdata(data["x"], data["y"], model)

    criterion = torch.nn.MSELoss(size_average=False)
    optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

    # 记录每个epoch的loss和epoch数
    losses = []
    epochs = []

    for epoch in range(40):
        # for step in range(5):

            optimizer.zero_grad()
            # Forward pass
            y_pred = model(data['x'])
            # Compute Loss
            loss = criterion(y_pred, data['y'])

            # Backward pass
            loss.backward()
            optimizer.step()
            losses.append(loss.detach().numpy())
            epochs.append(epoch + 1)
            # if epoch == 0 and step == 5:
            #     print("训练很少几个step的模型")
            #     print(y_pred.data.numpy())
            #     print(data['y'].numpy())
            #     plotdata(data["x"], data["y"], model)
            #
            # if epoch == 1 and step == 0:
            #     print("#训练一个epoch之后的模型")
            #     print(y_pred.data.numpy())
            #     print(data['y'].numpy())
            #     plotdata(data["x"], data["y"], model)

    print("训练结束")
    print(y_pred.data.numpy())
    print(data['y'].numpy())
    plotdata(data["x"], data["y"], model)

    # 绘制二维折线图
    plt.plot(epochs, losses)
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.title('Training Loss')
    plt.show()


