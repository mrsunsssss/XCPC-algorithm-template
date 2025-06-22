int mu[N];int phi[N];
int np[N];vector<int> p;
void Prework(int n = N - 10) {
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
