import torch.nn as nn
import torch
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


class TextClassificationModel(nn.Module):
    def __init__(self, vocab_size, embed_dim, num_class):
        super(TextClassificationModel, self).__init__()

        self.embedding = nn.EmbeddingBag(vocab_size,  # 词典大小
                                         embed_dim,  # 嵌入的维度
                                         sparse=False)  #
        self.fc = nn.Linear(embed_dim, num_class)
        self.init_weights()

    def init_weights(self):
        initrange = 0.5
        self.embedding.weight.data.uniform_(-initrange, initrange)  # 初始化权重
        self.fc.weight.data.uniform_(-initrange, initrange)
        self.fc.bias.data.zero_()  # 偏置值归零

    def forward(self, text, offsets):
        embedded = self.embedding(text, offsets)
        return self.fc(embedded)


# 实现基于RNN的文本分类
# 首先将文本通过embedding转换成连续的矩阵，然后使用双向循环神经网络提取特征，再接全连接层，实现分类预测。
class RNNTextClassifier(nn.Module):
    def __init__(self, vocab_size, embedding_dim, hidden_dim, num_classes):
        super(RNNTextClassifier, self).__init__()
        self.embedding = nn.EmbeddingBag(vocab_size, embedding_dim)
        self.rnn = nn.RNN(embedding_dim, hidden_dim, bidirectional=True)
        self.fc = nn.Linear(hidden_dim * 2, num_classes)

    def init_weights(self):
        initrange = 0.5
        self.embedding.weight.data.uniform_(-initrange, initrange)  # 初始化权重
        self.fc.weight.data.uniform_(-initrange, initrange)
        self.fc.bias.data.zero_()  # 偏置值归零

    def forward(self, text, offsets):
        embedded = self.embedding(text, offsets)
        out, _ = self.rnn(embedded.unsqueeze(1))
        out = self.fc(out[:, -1, :])
        return out


class LSTMClassificationModel(nn.Module):
    def __init__(self, vocab_size, embed_dim, hidden_dim, num_class):
        super(LSTMClassificationModel, self).__init__()

        self.embedding = nn.EmbeddingBag(vocab_size,  # 词典大小
                                         embed_dim,  # 嵌入的维度
                                         sparse=False)
        self.lstm = nn.LSTM(embed_dim, hidden_dim, batch_first=True, bidirectional=True)
        self.fc = nn.Linear(hidden_dim * 2, num_class)
        self.init_weights()

    def init_weights(self):
        initrange = 0.5
        self.embedding.weight.data.uniform_(-initrange, initrange)  # 初始化权重
        self.fc.weight.data.uniform_(-initrange, initrange)
        self.fc.bias.data.zero_()  # 偏置值归零

    def forward(self, text, offsets):
        embedded = self.embedding(text, offsets)
        lstm_out, _ = self.lstm(embedded.unsqueeze(1))
        out = self.fc(lstm_out[:, -1, :])
        return out


# 实现基于CNN的文本分类
# 首先将文本通过embedding转换成连续的矩阵，然后使用多层卷积神经网络提取特征，再接全连接层，实现分类预测。
class CNNTextClassifier(nn.Module):
    def __init__(self, vocab_size, embedding_dim, filter_sizes, num_filters, num_class):
        super(CNNTextClassifier, self).__init__()
        self.embedding = nn.EmbeddingBag(vocab_size, embedding_dim, sparse=False)
        self.convs = nn.ModuleList([
            nn.Conv1d(embedding_dim, num_filters, kernel_size=k, padding=k // 2)
            for k in filter_sizes
        ])
        self.fc = nn.Linear(num_filters * 3, num_class)

    def forward(self, text, offsets):
        embedded = self.embedding(text, offsets)
        embedded = embedded.unsqueeze(1).transpose(1, 2)
        conv_outs = [F.relu(conv(embedded)) for conv in self.convs]
        pooled_outs = [F.max_pool1d(out, out.size(2)).squeeze(2) for out in conv_outs]
        out = torch.cat(pooled_outs, dim=1)
        out = self.fc(out)
        return out


# 实现基于Transformer的文本分类
# 首先将文本通过embedding转换成连续的矩阵，然后使用Transformer提取特征，再接全连接层，实现分类预测。
class TransformerClassifier(nn.Module):
    def __init__(self, vocab_size, embed_dim, num_heads, num_layers, num_class):
        super(TransformerClassifier, self).__init__()
        self.embedding = nn.EmbeddingBag(vocab_size, embed_dim, sparse=False)
        transformer_encoder_layer = nn.TransformerEncoderLayer(d_model=embed_dim, nhead=num_heads)
        self.transformer_encoder = nn.TransformerEncoder(transformer_encoder_layer, num_layers=num_layers)
        self.fc = nn.Linear(embed_dim, num_class)

    def forward(self, text, offsets):
        embedded = self.embedding(text, offsets)
        transformer_out = self.transformer_encoder(embedded.unsqueeze(1))
        out = self.fc(transformer_out[:, -1, :])
        return out
