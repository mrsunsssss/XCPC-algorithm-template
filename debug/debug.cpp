template <class... Args>
void debug(const Args&... args) { ((cerr << args << ", "), ...) << '\n'; }
#define debug(args...) cerr << #args << ": ", debug(args)
