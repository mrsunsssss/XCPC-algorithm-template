https://codeforces.com/contest/2069/submission/306759050
抄的还没看

struct RollbackDSU 
{
    vector <int> par;
    stack <pair <int,int>> history;
    int cntcomp;
    RollbackDSU(int n) 
    {
        par.assign(n + 1, -1);
        cntcomp = n;
    }
    
    int find(int v) 
    {
        while(par[v] >= 0) v = par[v];
        return v;
    }
 
    bool unite(int a, int b) 
    {
        a = find(a);
        b = find(b);
        if(a == b) 
        {
            history.push({-1, -1});
            return false;
        }
        if(par[a] > par[b]) swap(a,b);
        history.push({a, par[a]});
        history.push({b, par[b]});
        par[a] += par[b];
        par[b] = a;
        cntcomp--;
        return true;
    }
 
    void rollback() 
    {
        auto top1 = history.top(); 
        history.pop();
        if(top1.first == -1 && top1.second == -1) 
        {
            return;
        }
        auto top2 = history.top(); 
        history.pop();
        int b = top1.first, bpar = top1.second;
        int a = top2.first, apar = top2.second;
        par[a] = apar;
        par[b] = bpar;
        cntcomp++;
    }
};
