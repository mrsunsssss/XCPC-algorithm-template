struct Liner_Base {//默认不能为空,需要判断0. 允许空集需要额外判断
    int n, m;
    vector<int> a;
    Liner_Base(vector<int>_a) :a(_a), n((int)_a.size() - 1) { gauss(); }
    Liner_Base() {
        a.push_back(0);
        n = m = 0;
    }
    void gauss() {//高斯消元，保证每个最高位只有最多一个数有
        int k = 1;
        for (int i = 60;i >= 0;i--) {
            for (int j = k;j <= n;j++) {
                if (a[j] >> i & 1) {
                    swap(a[j], a[k]);
                    break;
                }
            }
            if (~a[k] >> i & 1) continue;
            for (int j = 1;j <= n;j++) {
                if (j != k && (a[j] >> i & 1)) a[j] ^= a[k];
            }
            k++;
            if (k == n + 1) break;
        }
        m = k - 1;
    }
    int MAX() {//异或最大
        int res = 0;
        for (int i = 1;i <= m;i++) {
            if ((res ^ a[i]) > res) res ^= a[i];
        }
        return res;
    }
    int MAX(int x) {//异或上x最大
        int res = x;
        for (int i = 1;i <= m;i++) {
            if ((res ^ a[i]) > res) res ^= a[i];
        }
        return res;
    }
    int kth(int k) {//kth_min
        int res = 0;
        if (m < n) k--;//能凑出0
        if (k >= (1LL << m)) return -1;
        for (int i = 0;i < m;i++) {
            if (k >> i & 1) res ^= a[m - i];
        }
        return res;
    }
    int rank(int x) {//排名
        int res = 0;
        for (int i = 1;i <= m;i++) {
            if ((x ^ a[i]) < a[i]) x ^= a[i], res += 1LL << (m - i);
        }
        return res + (n > m);
    }
    int contains(int x) {//是否能异或出x
        for (int i = 1;i <= m;i++) {
            if ((x ^ a[i]) < x) x ^= a[i];
        }
        return x == 0;
    }
    void insert(int x) {//动态插入
        n++;
        for (int i = 1;i <= m;i++) {
            if ((x ^ a[i]) < x) x ^= a[i];
        }
        if (x) {
            m++;
            a.push_back(x);
            for (int i = m;i >= 2;i--) {
                if (a[i] > a[i - 1]) swap(a[i], a[i - 1]);
                else break;
            }
        }
        //消元,如果不需要消元的性质可以去掉
        for (int i = 1;i <= m;i++) {
            int t = __lg(a[i]);
            for (int j = 1;j < i;j++) {
                if ((a[j] >> t & 1)) a[j] ^= a[i];
            }
        }
    }
 
    int size() {
        return m;
    }
};
