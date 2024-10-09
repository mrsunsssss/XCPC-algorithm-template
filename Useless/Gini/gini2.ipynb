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
        if self.root:
            return self.label
        feature_value = features[self.feature_name]
        if feature_value in self.tree:
            return self.tree[feature_value].predict(features)
        else:
            return None

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

    # 基尼增益比
    def gini_gain_ratio(self, datasets, idx):
        if len(datasets) == 0:  # 处理数据集为空的情况
            return 0
        gini = self.calc_gini(datasets)
        cond_gini_value = self.cond_gini(datasets, idx)
        gain = gini - cond_gini_value #计算基尼增益

         # 计算复杂度惩罚
        unique_vals = len(set(datasets[:, idx]))  # 统计特征值的种类数量
        complexity_penalty = unique_vals / len(datasets)  # 计算复杂度惩罚

        # 计算增益比
        if complexity_penalty == 0:  # 避免除以零
            return 0
        return gain / complexity_penalty
        
    def gini_gain_train(self, datasets):
        sz = len(datasets[0]) - 1
        best_gain_ratio = -1
        best_feature = -float("inf")
    
        for c in range(sz):
            gain_ratio = self.gini_gain_ratio(datasets, c)
            if gain_ratio > best_gain_ratio:
                best_gain_ratio = gain_ratio
                best_feature = c
    
        return best_feature, best_gain_ratio  # 返回特征索引和基尼增益比

    def train(self, train_data):
        """
        input: 数据集D(DataFrame格式)，特征集A，阈值eta
        output: 决策树T
        """
        _, y_train, features = train_data.iloc[:, :-1], train_data.iloc[:, -1], train_data.columns[:-1]
    
        # 1, 若D中实例属于同一类Ck，则T为单节点树，并将类Ck作为结点的类标记，返回T
        if len(y_train.value_counts()) == 1:
            return Node(root=True, label=y_train.iloc[0])

        # 2, 若A为空，则T为单节点树，将D中实例数最大的类Ck作为该节点的类标记，返回T
        if len(features) == 0:
            return Node(
                root=True,
                label=y_train.value_counts().sort_values(ascending=False).index[0]
            )

        # 3, 计算最大基尼增益比
        max_feature, max_gain_ratio = self.gini_gain_train(train_data.values)
        max_feature_name = features[max_feature]

        # 4, 如果增益比小于阈值，置T为单节点树，并将D中实例数最大的类Ck作为该节点的类标记，返回T
        if max_gain_ratio < self.epsilon:
            return Node(
                root=True,
                label=y_train.value_counts().sort_values(ascending=False).index[0]
            )

        # 5, 构建Ag子集
        node_tree = Node(root=False, feature_name=max_feature_name, feature=max_feature)

        # 获取特征值列表
        feature_list = train_data[max_feature_name].value_counts().index
        for f in feature_list:
            sub_train_df = train_data.loc[train_data[max_feature_name] == f].drop([max_feature_name], axis=1)

            # 6, 递归生成树
            sub_tree = self.train(sub_train_df)
            node_tree.tree[f] = sub_tree  # 这里使用 tree 字典来存储子树

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
sample = {'multiValueFeature': 8, 'gender': 'F', 'carType': 'Family', 'shirtSize': 'Extra Large'}
prediction = tree.predict(sample)
print('预测结果:', prediction)

