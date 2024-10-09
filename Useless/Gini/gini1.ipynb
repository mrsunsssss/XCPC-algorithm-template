import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
%matplotlib inline

from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from collections import Counter
import math
from math import log
import pprint

# 书上题目5.1
def create_data():
    datasets = [['青年', '否', '否', '一般', '否'],
               ['青年', '否', '否', '好', '否'],
               ['青年', '是', '否', '好', '是'],
               ['青年', '是', '是', '一般', '是'],
               ['青年', '否', '否', '一般', '否'],
               ['中年', '否', '否', '一般', '否'],
               ['中年', '否', '否', '好', '否'],
               ['中年', '是', '是', '好', '是'],
               ['中年', '否', '是', '非常好', '是'],
               ['中年', '否', '是', '非常好', '是'],
               ['老年', '否', '是', '非常好', '是'],
               ['老年', '否', '是', '好', '是'],
               ['老年', '是', '否', '好', '是'],
               ['老年', '是', '否', '非常好', '是'],
               ['老年', '否', '否', '一般', '否'],
               ]
    labels = [u'年龄', u'有工作', u'有自己的房子', u'信贷情况', u'类别']
    # 返回数据集和每个维度的名称
    return datasets, labels

# 教材p108习题2
def create_data_2():
    datasets =[[1,'M','Family','Small','C0'],
               [2,'M','Sports','Medium','C0'],
               [3,'M','Sports','Medium','C0'],
               [3,'M','Sports','Large','C0'],
               [4,'M','Sports','Extra Large','C0'],
               [4,'M','Sports','Extra Large','C0'],
               [5,'F','Sports','Small','C0'],
               [5,'F','Sports','Small','C0'],
               [6,'F','Sports','Medium','C0'],
               [7,'F','Luxury','Large','C0'],
               [7,'M','Family','Large','C1'],
               [8,'M','Family','Extra Large','C1'],
               [9,'M','Family','Medium','C1'],
               [10,'M','Luxury','Extra Large','C1'],
               [11,'F','Luxury','Small','C1'],
               [12,'F','Luxury','Small','C1'],
               [13,'F','Luxury','Medium','C1'],
               [14,'F','Luxury','Medium','C1'],
               [15,'F','Luxury','Medium','C1'],
               [16,'F','Luxury','Large','C1']
               ]
    labels = [u'multiValueFeature', u'gender', u'carType', u'shirtSize', u'类别']
    # 返回数据集和每个维度的名称
    return datasets, labels

# 定义节点类 二叉树
class Node:
    def __init__(self, root=True, label=None, feature_name=None, feature=None):
        self.root = root
        self.label = label
        self.feature_name = feature_name
        self.feature = feature
        self.tree = {}
        self.result = {
            'label:': self.label,
            'feature': self.feature,
            'tree': self.tree
        }

    def __repr__(self):
        return '{}'.format(self.result)

    def add_node(self, val, node):
        self.tree[val] = node

    def predict(self, features):
        if self.root is True:
            return self.label
        return self.tree[features[self.feature]].predict(features)


class DTree:
    def __init__(self, epsilon=0.1):
        self.epsilon = epsilon
        self._tree = {}

    def calc_gini(self, datasets):
        sz = len(datasets)
        mp = Counter()
        for i in range(0, sz):
            x = datasets[i][-1]
            if x not in mp:
                mp[x] = 0
            mp[x] += 1
        gini = 1 - sum([(cnt / sz) ** 2 for cnt in mp.values()])
        return gini

    def cond_gini(self, datasets, idx=0):
        sz = len(datasets)
        mp = {}
        for i in range(0, sz):
            x = datasets[i][idx]
            if x not in mp:
                mp[x] = []
            mp[x].append(datasets[i])
        cond_gini = sum([(len(p) / sz) * self.calc_gini(p) for p in mp.values()])
        return cond_gini

    def gini_gain(self, gini, cond_gini):
        return gini - cond_gini

    def gini_gain_train(self, datasets):
        sz = len(datasets[0]) - 1
        gini = self.calc_gini(datasets)
        mp = []
        for c in range(0, sz):
            c_gini_gain = self.gini_gain(gini, self.cond_gini(datasets, c))
            mp.append((c, c_gini_gain))
            #print('特征({}) - gini_gain - {:.3f}'.format(labels[c], c_gini_gain))
        # 返回gini增益最大的特征
        return max(mp, key=lambda x: x[1])

    def train(self, train_data):
        """
        构建决策树
        """
        _, y_train, features = train_data.iloc[:, :-1], train_data.iloc[:, -1], train_data.columns[:-1]

        # 1, 若所有样本属于同一类
        if len(y_train.value_counts()) == 1:
            return Node(root=True, label=y_train.iloc[0])

        # 2, 若没有特征可以继续分裂，返回出现次数最多的类别
        if len(features) == 0:
            return Node(root=True, label=y_train.value_counts().idxmax())

        # 3, 找到基尼增益最大的特征
        max_feature, max_gini_gain = self.gini_gain_train(np.array(train_data))
        max_feature_name = features[max_feature]

        # 4, 若基尼增益小于阈值，返回样本中出现最多的类别
        if max_gini_gain < self.epsilon:
            return Node(root=True, label=y_train.value_counts().idxmax())

        # 5, 创建树节点
        node_tree = Node(root=False, feature_name=max_feature_name, feature=max_feature)

        feature_list = train_data[max_feature_name].value_counts().index
        for f in feature_list:
            sub_train_df = train_data[train_data[max_feature_name] == f].drop([max_feature_name], axis=1)
            sub_tree = self.train(sub_train_df)  # 递归构建子树
            node_tree.add_node(f, sub_tree)

        return node_tree

    def fit(self, train_data):
        self._tree = self.train(train_data)
        return self._tree

    def predict(self, X_test):
        return self._tree.predict(X_test)


datasets, labels = create_data_2()
data_df = pd.DataFrame(datasets, columns=labels)
dt = DTree(0.1)
tree = dt.fit(data_df)

tree
#sample = {'multiValueFeature': 8, 'gender': 'F', 'carType': 'Family', 'shirtSize': 'Extra Large'}
#sample = ['青年','否','否','一般']
sample = [8, 'F', 'Family','Extra Large']
prediction = tree.predict(sample)
print('预测结果:', prediction)

