template <class... Args>
void debug(const Args&... args) { ((cerr << args << ", "), ...) << '\n'; }
#define debug(args...) cerr << #args << ": ", debug(args)


template <class... Args> void myin(Args&... args) { ((cin >> args), ...); }
template <class... Args> void myout(const Args&... args) { ((cout << args), ...); }
//ofstream mcout("C:/Users/Mrsuns/Desktop/out.txt");
//ofstream mcout("C:/Users/Mrsuns/Desktop/out.txt");
