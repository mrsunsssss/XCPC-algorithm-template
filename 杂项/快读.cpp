char In[1 << 20], * ss = In, * tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)

int read(char ch = 0) {
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') f = ch == '-' ? -1 : 1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
char getch(char ch = 0) {
    while (ch < 'A' || (ch > 'Z' && ch < 'a') || ch > 'z') ch = getchar();
    return ch;
}
inline void write(ull x) {
    if (x < 0)putchar('-'), x = -x;
    if (x > 9)write(x / 10ll);
    putchar(x % 10 + 48);
}
