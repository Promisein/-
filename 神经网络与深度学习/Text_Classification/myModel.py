import torch.nn as nn
import torch
from torch.nn import TransformerEncoder, TransformerEncoderLayer
import torch.nn.functional as F


# 实现基于全连接的文本分类模型
# 首先将文本通过embedding转换成连续的矩阵，然后在其上使用pooling方法，再接全连接层，实现分类预测。
class EmbedClassifier(nn.Module):
    def __init__(self, vocab_size, embed_dim, hidden_dim, num_class):
        super(EmbedClassifier, self).__init__()
        self.embedding = nn.Embedding(vocab_size, embed_dim)
        self.fc1 = nn.Linear(embed_dim, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, num_class)

    def forward(self, x):
        embedded = self.embedding(x)
        pooled = F.avg_pool2d(embedded, (embedded.shape[1], 1)).squeeze(1)
        hidden = F.relu(self.fc1(pooled))
        output = self.fc2(hidden)
        return output


# 实现基于RNN的文本分类
# 首先将文本通过embedding转换成连续的矩阵，然后使用双向循环神经网络提取特征，再接全连接层，实现分类预测。
class RNNTextClassifier(nn.Module):
    def __init__(self, vocab_size, embedding_dim, hidden_dim, num_classes):
        super(RNNTextClassifier, self).__init__()
        self.embedding = nn.Embedding(vocab_size, embedding_dim)
        self.rnn = nn.RNN(embedding_dim, hidden_dim, bidirectional=True)
        self.fc = nn.Linear(hidden_dim * 2, num_classes)

    def forward(self, x, hidden_dim=16):
        embedded = self.embedding(x)
        output, _ = self.rnn(embedded)
        hidden = torch.cat((output[:, -1, :hidden_dim], output[:, 0, hidden_dim:]), dim=1)  # 拼接双向RNN的输出
        output = self.fc(hidden)
        return output


# 实现基于CNN的文本分类
# 首先将文本通过embedding转换成连续的矩阵，然后使用多层卷积神经网络提取特征，再接全连接层，实现分类预测。
class CNNTextClassifier(nn.Module):
    def __init__(self, vocab_size, embedding_dim, num_filters, filter_sizes, num_class):
        super(CNNTextClassifier, self).__init__()
        self.embedding = nn.Embedding(vocab_size, embedding_dim)
        self.convs = nn.ModuleList([
            nn.Conv2d(1, num_filters, (filter_size, embedding_dim))
            for filter_size in filter_sizes
        ])
        self.fc = nn.Linear(num_filters * len(filter_sizes), num_class)

    def forward(self, x):
        embedded = self.embedding(x)
        embedded = embedded.unsqueeze(1)  # 扩展维度以适应卷积操作
        feature_maps = [F.relu(conv(embedded)).squeeze(3) for conv in self.convs]  # 多层卷积操作
        pooled = [F.max_pool1d(feature_map, feature_map.size(2)).squeeze(2) for feature_map in feature_maps]
        hidden = torch.cat(pooled, dim=1)  # 拼接池化结果
        output = self.fc(hidden)
        return output


# 实现基于Transformer的文本分类
# 首先将文本通过embedding转换成连续的矩阵，然后使用Transformer提取特征，再接全连接层，实现分类预测。
class TransformerClassifier(nn.Module):
    def __init__(self, vocab_size, embed_dim, hidden_dim, num_heads, num_layers, num_class):
        super( TransformerClassifier, self).__init__()
        self.embedding = nn.Embedding(vocab_size, embed_dim)
        self.transformer = nn.Transformer(
            d_model=embed_dim,
            nhead=num_heads,
            num_encoder_layers=num_layers,
            num_decoder_layers=num_layers
        )
        self.fc = nn.Linear(embed_dim, num_class)

    def forward(self, x):
        embedded = self.embedding(x)
        embedded = embedded.permute(1, 0, 2)  # 调整维度顺序以适应Transformer
        output = self.transformer(embedded, embedded)  # Transformer层，使用相同的源输入作为目标输入
        output = output.permute(1, 0, 2)  # 调整维度顺序
        output = output.mean(dim=1)  # 对时间维度求平均
        output = self.fc(output)
        return output
