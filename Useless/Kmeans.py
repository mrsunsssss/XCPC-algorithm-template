import numpy as np
class KMeans:
    def __init__(self,k=3,times=100):
        self.k=k
        self.times=times
    def dis(self, p, cent):
        # 计算给定点到所有中心点的欧几里得距离
        a = [(np.sum((p-x)**2))**0.5 for x in cent]
        return a
    # 将每个点分配给最近的中心点
    def assign_lable(self, X):
        # 计算每个数据点到所有中心点的距离
        a = np.array([self.dis(x, self.cent) for x in X])
        # 返回每个点最近的中心点的索引
        return np.argmin(a, axis=1)
    def upd_cent(self, X):
        # 更新每个簇的中心点，取簇内所有点的均值
        return np.array([X[self.labels == i].mean(axis=0) for i in range(self.k)])
    def fit(self,X):
        # 选k个作为中心
        self.cent = X[np.random.choice(X.shape[0],self.k,replace=False)]
        for _ in range(self.times):
            # 进行聚类分配，获取每个点的标签
            self.labels = self.assign_lable(X)
            # 更新聚类中心点
            ncent = self.upd_cent(X)
            # 检查中心点是否收敛
            if np.all(ncent == self.cent):
                break
            self.cent = ncent
