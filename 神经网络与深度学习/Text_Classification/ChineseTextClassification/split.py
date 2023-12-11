import pandas as pd
import random

# 读取csv文件
data = pd.read_csv('./data/simplifyweibo_4_moods.csv')

# 随机打乱数据
data = data.sample(frac=1, random_state=1)

# 计算分割点
split_point = int(len(data) * 0.9)

# 分割数据
train_data = data[:split_point]
test_data = data[split_point:]

# 写入训练数据
train_data.to_csv('./data/train_data.csv', index=False)

# 写入测试数据
test_data.to_csv('./data/test_data.csv', index=False)
