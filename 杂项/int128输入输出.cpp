istream& operator>>(istream& cin, __int128& a) {
    a = 0;
    string scan;
    cin >> scan;
    for (int i = 0; i < scan.size(); i++) {
        a *= 10;
        a += scan[i] - '0';
    }
    return cin;
}
ostream& operator<<(ostream& cout, __int128 a) {
    if (a < 0) {
        cout << "-";
        a = -a;
    }
    if (a > 9)
        cout << a / 10;
    cout << (char)(a % 10 + '0');
    return cout;
}
