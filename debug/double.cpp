//读double
string s;cin >> s;
double x = stod(s);
long double y = stold(s);

//四舍五入
double x;cin>>x;
int y = floor(x+0.5);//根据精度设置，也有可能0.05，0.005...
int y = round(x);
