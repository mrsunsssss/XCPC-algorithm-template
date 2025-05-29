int rd(int l, int r) {
    static mt19937_64 gen(random_device{}());
    return uniform_int_distribution<int>(l, r)(gen);
}
