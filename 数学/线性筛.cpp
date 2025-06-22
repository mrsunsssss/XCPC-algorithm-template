int mu[N];int phi[N];
int np[N];vector<int> p;
void Prework(int n = N - 10) {//线性筛积性函数
    np[0] = np[1] = 1;mu[1] = 1;phi[1] = 1;
    for (int i = 2;i <= n;i++) {
        if (!np[i]) {
            p.push_back(i);
            mu[i] = -1;phi[i] = i - 1;
        }
        for (auto j : p) {
            if (i * j > n) break;
            np[i * j] = 1;
            if (i % j == 0) {
                phi[i * j] = phi[i] * j;
                break;
            }
            else {
                mu[i * j] = -mu[i];
                phi[i * j] = phi[i] * (j - 1);
            }
        }
    }
}


const int N = 1e5 + 10;
int np[N], minp[N];
vector<int> p;
void Prework(int n = N - 10) {//欧拉筛最小质因子
    np[0] = np[1] = 1;
    for (int i = 2;i <= n;i++) {
        if (!np[i]) {
            p.push_back(i);
            minp[i] = i;
        }
        for (auto j : p) {
            if (i * j > n) break;
            np[i * j] = 1;
            minp[i * j] = j;
            if (i % j == 0) break;
        }
    }
}

vector<int> Factor(int x) {
    vector<int> a;
    while (x > 1) {
        int t = minp[x];
        while (x % t == 0) x /= t;
        a.push_back(t);
    }
    return a;
}

vector<int> Divisor(int x) {//获取所有因子
    vector<array<int, 2>> a;
    while (x > 1) {
        if (a.size() == 0 || a.back()[0] != minp[x]) {
            a.push_back({ minp[x],1 });
        }
        else {
            a.back()[1]++;
        }
        x /= minp[x];
    }
    vector<int> ret = { 1 };
    for (auto [num, cnt] : a) {
        int val = 1;
        int sz = ret.size();
        for (int j = 1;j <= cnt;j++) {
            val *= num;
            for (int j = 0;j < sz;j++) {
                ret.push_back(ret[j] * val);
            }
        }
    }
    return ret;
}
int Divisor_cnt(int x) {
    int res = 1;
    while (x > 1) {
        int P = minp[x], cnt = 0;
        while (x % P == 0) x /= P, cnt++;
        res *= cnt + 1;
    }
    return res;
}
int Divisor_sum(int x) {
    int res = 1;
    while (x > 1) {
        int P = minp[x], pw = 1, sum = 1;
        while (x % P == 0) x /= P, pw *= P, sum += pw;
        res *= sum;
    }
    return res;
}
