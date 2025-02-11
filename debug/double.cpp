//读double
string s;cin >> s;
double x = stod(s);
long double y = stold(s);

//double 转 int (给了一个接近整数的long double)
double x;cin>>x;
int y = floor(x+0.1);//floor(x+0.5)

//四舍五入
double x;cin>>x;
int y = x+0.5;
