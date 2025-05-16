mt19937 gen(random_device{}());
auto getrd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}
