#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

bool Memory_begin;

//板子

bool Memory_end;

void Prework() {
    
}
void Solve() {
    cerr << (&Memory_end - &Memory_begin) / 1048576.0 << "MB" << '\n';

}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    Prework();
    while (T--) Solve();
}
