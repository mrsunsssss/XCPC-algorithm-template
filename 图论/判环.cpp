vector<int> vis(n + 1);
vector<int> stk(n + 1);int top = 0;
vector<int> loop;
auto dfs = [&](auto&& dfs, int u, int p) {
    vis[u] = 1;stk[++top] = u;
    for (auto v : g[u]) {
        //if (v == p) continue;//如果不需要二元环或是无向图则加上这句
        if (vis[v] == 1) {//遇到了还没出栈的点，说明找到了环
            do {
                loop.push_back(stk[top]);
                if (stk[top] == v) break;
                top--;
            } while (1);
            return 1;
        }
        else if (vis[v] == 0) {
            if (dfs(dfs, v, u)) return 1;//不能直接return dfs;因为这里没找到，可能在其他地方找到
        }
    }
    vis[u] = 2;
    top--;
    return 0;
    };
