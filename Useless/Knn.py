class KNN:
    def __init__(self, k=3):
        self.k = k

    def fit(self, X, y):
        self.X = X
        self.y = y

    def predict(self, X):
        predictions = [self._predict(x) for x in X]
        return predictions

    def _predict(self, x):
        # 计算距离
        distances = [self.distance(xx, x) for xx in self.X]
        I = [i for i in range(0,len(distances))]
        # 找到最近的 K 个样本
        k_indices = sorted(I, key=lambda i: distances[i])[0 : self.k]
        # 获取 K 个最近样本的标签
        k_labels = [self.y[i] for i in k_indices]
        # 进行投票
        cnt = {}
        for i in k_labels :
            if i in cnt:
                cnt[i] += 1
            else:
                cnt[i] = 1
        return max(cnt,key = cnt.get)

    def distance(self, point1, point2):
        # 计算欧几里得距离
        ret=0
        for i in range(0,len(point1)):
            ret += (point1[i]-point2[i])**2
        return ret**0.5

# 示例用法
if __name__ == "__main__":
    # 示例数据（特征和标签）
    X_train = [[1, 2], [2, 3], [3, 1], [6, 5], [7, 7]] #特征
    y_train = [0, 1, 2, 0, 1] #标签

    X_test = [[1, 2], [5, 5]]

    # 创建 KNN 实例
    knn = KNN(k=3)
    knn.fit(X_train, y_train)
    predictions = knn.predict(X_test)

    print("Predictions:", predictions)
