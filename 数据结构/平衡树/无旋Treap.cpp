mt19937 rng(random_device{}());
//mt19937 rng(99999989);
template <typename T> struct Treap {
#define ls(u) (tr[u].ls)
#define rs(u) (tr[u].rs)
    struct node {
        //origin
        int ls, rs, key, sz;
        T val;
        //extend
        bool tag;//区间翻转标记
        //int fa;//父节点,一般用于维护序列中查找指定节点的中序值.
    };

    static node tr[N];
    inline static int stk[N];
    int root, T1, T2, T3;
    inline static int Top, idx;

    //O(n) build a Treap needed.
    inline static int BUILD_STACK[N], TOP;

    Treap() {
        root = T1 = T2 = T3 = 0;
    }
    ~Treap() {
        for (int i = 1;i <= idx;i++) {
            tr[i] = { 0,0,0,0,0,0 };
        }
        root = idx = Top = 0;
    }
    int BUILD(const vector<T>& vec) {//O(n) build a Treap.
        for (auto i : vec) {
            int id = newnode(i), lst = 0;
            while (TOP && tr[BUILD_STACK[TOP]].key > tr[id].key) {//笛卡尔树建树
                pushup(BUILD_STACK[TOP]);
                lst = BUILD_STACK[TOP--];
            }
            if (TOP) rs(BUILD_STACK[TOP]) = id;
            ls(id) = lst;
            BUILD_STACK[++TOP] = id;
        }
        while (TOP) pushup(BUILD_STACK[TOP--]);
        return BUILD_STACK[1]; //树根
    }

    node operator[](int i) const { return tr[i]; }
    int size() { return tr[root].sz; }//总大小
    int newnode(T val) {
        int nn = Top ? stk[Top--] : ++idx;
        tr[nn] = { 0,0, (int)rng(), 1,val,0 };
        return nn;
    }
    void pushup(int u) {
        tr[u].sz = tr[ls(u)].sz + tr[rs(u)].sz + 1;
        //维护父节点
        /*
        if (ls(u)) tr[ls(u)].fa = u;
        if (rs(u)) tr[rs(u)].fa = u;
        if (ls(tr[u].fa) != u && rs(tr[u].fa) != u) tr[u].fa = 0;
        */
    }

    int merge(int u, int v) {
        if (!u || !v) return u + v;
        if (tr[u].key > tr[v].key) {
            pushdown(u);
            rs(u) = merge(rs(u), v);
            pushup(u);
            return u;
        }
        else {
            pushdown(v);
            ls(v) = merge(u, ls(v));
            pushup(v);
            return v;
        }
    }


    //序列操作

    void pushdown(int u) {
        if (tr[u].tag) {
            if (ls(u)) OP_REV(ls(u));
            if (rs(u)) OP_REV(rs(u));
            tr[u].tag = 0;
        }
    }

    //按排名分裂
    void split_order(int u, int k, int& x, int& y) {
        if (!u) {
            x = y = 0;
            return;
        }
        pushdown(u);
        int s = tr[ls(u)].sz + 1;
        if (k < s) {
            y = u;
            split_order(ls(u), k, x, ls(u));
        }
        else {
            x = u;
            split_order(rs(u), k - s, rs(u), y);
        }
        pushup(u);
    }

    //维护序列时的插入,选择插入到哪个位置
    void insert_order(T val, int k) {
        split_order(root, k, T1, T2);
        root = merge(merge(T1, newnode(val)), T2);
    }
    //在某位置插入一段序列(插入了一整棵树),复杂度O(size(vec))
    void INSERT_order(int k, const vector<T>& vec) {
        split_order(root, k, T1, T2);
        root = merge(merge(T1, BUILD(vec)), T2);
    }
    //插入到序列末尾
    void push_back(T val) {
        root = merge(root, newnode(val));
    }

    //删除指定位置[l,r]的元素
    void erase_order(int l, int r) {
        split_order(root, l - 1, T1, T2);
        split_order(T2, r - l + 1, T2, T3);
        auto del = [&](auto&& del, int u) {
            if (!u) return;
            stk[++Top] = u;
            if (ls(u)) del(del, ls(u));
            if (rs(u)) del(del, rs(u));
            };
        del(del, T2);
        root = merge(T1, T3);
    }

    //查找中序遍历第k个元素
    T kth_order(int k) {
        split_order(root, k - 1, T1, T2);
        split_order(T2, 1, T2, T3);
        T res = tr[T2].val;
        root = merge(T1, merge(T2, T3));
        return res;
    }
    /*
    //查找节点是中序遍历的第几个元素
    int rank_order(int u) {
        int res = tr[ls(u)].sz + 1;
        while (tr[u].fa) {
            if (rs(tr[u].fa) == u) res += tr[ls(tr[u].fa)].sz + 1;
            u = tr[u].fa;
        }
        return res;
    }
    */
    //下传翻转标记
    void OP_REV(int u) {
        swap(ls(u), rs(u));
        tr[u].tag ^= 1;
    }
    //区间翻转
    void reverse(int l, int r) {
        split_order(root, l - 1, T1, T2);
        split_order(T2, r - l + 1, T2, T3);
        OP_REV(T2);
        root = merge(T1, merge(T2, T3));
    }

    //集合操作

    //按值分裂
    void split(int u, T val, int& x, int& y) {
        if (!u) {
            x = y = 0;
            return;
        }
        if (tr[u].val > val) {
            y = u;
            split(ls(u), val, x, ls(u));
        }
        else if (tr[u].val <= val) {
            x = u;
            split(rs(u), val, rs(u), y);
        }
        pushup(u);
    }

    //维护集合时的插入
    void insert(T val) {
        split(root, val, T1, T2);
        root = merge(merge(T1, newnode(val)), T2);
    }

    //删除
    void remove(T val) {
        split(root, val, T1, T2);
        split(T1, val - 1, T1, T3);
        T3 = merge(ls(T3), rs(T3));
        root = merge(merge(T1, T3), T2);
    }
    //带垃圾回收的删除
    void erase(T val) {
        split(root, val, T1, T2);
        split(T1, val - 1, T1, T3);
        if (T3) {
            if (Top < (N >> 8) - 5) stk[++Top] = T3;
        }
        T3 = merge(ls(T3), rs(T3));
        root = merge(merge(T1, T3), T2);
    }
    //小于val的个数+1
    int rank(T val) {
        split(root, val - 1, T1, T2);
        int res = tr[T1].sz + 1;
        root = merge(T1, T2);
        return res;
    }
    int __rank(T val) {//递归改循环
        int u = root;
        int ret = 1;
        while (u) {
            if (tr[u].val < val) {
                ret += tr[ls(u)].sz + 1;
                u = rs(u);
            }
            else {
                u = ls(u);
            }
        }
        return ret;
    }
    //第k小
    T kth(int k) {
        int u = root;
        while (u) {
            int s = tr[ls(u)].sz + 1;
            if (s == k) break;
            else if (k < s) u = ls(u);
            else k -= s, u = rs(u);
        }
        return tr[u].val;
    }
    //val的前驱
    T find_pre(T val) {
        split(root, val - 1, T1, T2);
        int u = T1;
        while (rs(u)) u = rs(u);
        root = merge(T1, T2);
        return tr[u].val;
    }
    static constexpr long long INF = std::numeric_limits<long long>::max();
    T __find_pre(T val) {//递归改循环
        int u = root, ret = -1;
        while (u) {
            if (tr[u].val < val) {
                ret = u;
                u = rs(u);
            }
            else {
                u = ls(u);
            }
        }
        return (ret == -1) ? -INF : tr[ret].val;
    }
    //val的后继
    T find_next(T val) {
        split(root, val, T1, T2);
        int u = T2;
        while (ls(u)) u = ls(u);
        root = merge(T1, T2);
        return tr[u].val;
    }
    T __find_next(T val) {//递归改循环
        int u = root, ret = -1;
        while (u) {
            if (tr[u].val <= val) {
                u = rs(u);
            }
            else {
                ret = u;
                u = ls(u);
            }
        }
        return (ret == -1) ? INF : tr[ret].val;
    }

    //l<=val<=r的数量
    int count(T l, T r) {
        split(root, r, T1, T2);
        split(T1, l - 1, T1, T3);
        int res = tr[T3].sz;
        root = merge(merge(T1, T3), T2);
        return res;
    }

    void join(int x, int y) {
        auto run = [&](auto&& run, int x, int y) {
            if (!x || !y) return x + y;
            if (tr[x].key < tr[y].key) swap(x, y);
            int L1 = ls(x), R1 = rs(x), L2 = 0, R2 = 0;
            split(y, tr[x].val, L2, R2), split(L2, tr[x].val - 1, L2, T1);
            if (T1) {
                tr[x].sz += tr[T1].sz;
                //sum,cnt...
            }
            ls(x) = run(run, L1, L2), rs(x) = run(run, R1, R2);
            pushup(x);
            return x;
            };
        root = run(run, x, y);
    }

    vector<T> elements() {
        vector<T> res;
        auto dfs = [&](auto&& dfs, int u)->void {
            if (!u) return;
            pushdown(u);
            dfs(dfs, ls(u));
            res.push_back(tr[u].val);
            dfs(dfs, rs(u));
            };
        dfs(dfs, root);
        return res;
    }
    void Delete() {//删除该根节点的子树
        auto del = [&](auto&& del, int u) {
            if (!u) return;
            stk[++Top] = u;
            if (ls(u)) del(del, ls(u));
            if (rs(u)) del(del, rs(u));
            };
        del(del, root);
    }

#undef ls
#undef rs 
};
template<typename T> typename Treap<T>::node Treap<T>::tr[N];
//基本功能是维护集合(set),也可以用于维护序列(vector). 
