#ifdef LOCAL
template <class... Args> void debug(const Args&... args) { ((cerr << args << ", "), ...) << '\n'; }
#define debug(args...) cerr << #args << ": ", debug(args)
#define debugsq(x) cerr << #x << ": ["; for (auto i : x) cerr << i << ' '; cerr << "]\n";
#define debugmp(x) cerr << #x << ": [ "; for (auto [i, j] : x) cerr << '[' << i << "," << j << "] "; cerr << "]\n";
#else
#define debug(...) ;
#define debugsq(...) ;
#define debugmp(...) ;
#endif


template <class... Args> void myin(Args&... args) { ((cin >> args), ...); }
template <class... Args> void myout(const Args&... args) { ((cout << args), ...); }

ofstream fcout("C:/Users/Mrsuns/Desktop/out.txt");
ofstream fcout("C:/Users/Mrsuns/Desktop/out.txt");
