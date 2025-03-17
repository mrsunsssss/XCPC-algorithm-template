while (!cin.eof()) {//文件不到end不结束}
getline(cin,s); //cin读取一整行到s,默认用\n分割
getline(stringstream ss,s,char x) 读取ss到s中，用x分割
string s = {char(-128)}；用initailize_list<char> 初始化s，把一个ascii码为-128的字符初始化为s。
s.find(string t,int pos);在s的第pos位开始找字符串t，返回找到的字符串t的首字母位置，位置下标皆从0开始，未找到返回string::npos，即-1。pos不填默认为0.
s.replace(int pos,int len,string t);将s的第pos个位置开始起的len个字符替换成字符串t。
s.substr(int pos,int len);将s的第pos个位置开始的len个字符取出。len不填默认为取到字符串s的末尾。
cin.get()；关闭同步流之后可以替换getchar();
cin.ignore()：忽略输入流中的 1 个字符。一般用于忽略换行。
cin.ignore(n)：忽略输入流中的 n 个字符。
cin.ignore(n, char x)：忽略输入流中的最多 n 个字符，或者直到遇到指定的分隔符 x。
