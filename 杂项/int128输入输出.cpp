istream& operator>>(istream& cin, __int128& a) {
    a = 0;__int128 f = 1;
    string s;cin >> s;
    for (auto i : s) {
        if (i == '-') { f = -1; continue; }
        a = a * 10 + (i - '0');
    }
    a *= f;
    return cin;
}
ostream& operator<<(ostream& cout, __int128 a) {
    if (a < 0) {
        cout << "-";
        a = -a;
    }
    if (a > 9) cout << a / 10;
    cout << (char)(a % 10 + '0');
    return cout;
}
