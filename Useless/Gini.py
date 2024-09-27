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

datasets, labels = create_data()

train_data = pd.DataFrame(datasets, columns = labels)

train_data

# 基尼指数
def calc_gini(datasets):
    sz = len(datasets)
    mp = Counter()
    for i in range(0, sz):
        x = datasets[i][-1]
        if x not in mp:
            mp[x] = 0
        mp[x] += 1
    gini = 1 - sum([(cnt / sz) ** 2 for cnt in mp.values()])
    return gini

# 条件基尼指数
def cond_gini(datasets, idx = 0):
    sz = len(datasets)
    mp = {}
    for i in range(0, sz):
        x = datasets[i][idx]
        if x not in mp:
            mp[x] = []
        mp[x].append(datasets[i])
    cond_gini = sum([(len(p) / sz) * calc_gini(p) for p in mp.values()])
    return cond_gini

# 信息增益
def gini_gain(gini, cond_gini):
    return gini - cond_gini


def gini_gain_train(datasets):
    sz = len(datasets[0]) - 1
    gini = calc_gini(datasets)
    mp = []
    for c in range(0, sz):
        c_gini_gain = gini_gain(gini, cond_gini(datasets, c))
        mp.append((c, c_gini_gain))
        print('特征({}) - gini_gain - {:.3f}'.format(labels[c], c_gini_gain))
    # 比较大小
    A = max(mp, key=lambda x: x[1])
    return '特征({})的基尼增益最大，选择为根节点特征'.format(labels[A[0]])

gini_gain_train(np.array(datasets))
