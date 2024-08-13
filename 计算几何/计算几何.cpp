#define debugP(x) cerr<<#x<<":("<<x[0]<<','<<x[1]<<")"<<endl
using ld = long double;
using P = array<int, 2>;
using LI = array<P, 2>;
using PD = array<ld, 2>;
using LD = array<PD, 2>;
using CI = vector<P>;
using CD = vector<PD>;
const ld eps = 1e-9;
 
int prev(int i, int n) {
    return i == 0 ? n - 1 : i - 1;
}
int next(int i, int n) {
    return i == n - 1 ? 0 : i + 1;
}
 
int sgn(ld x) {
    return x > eps ? 1 : (x < -eps ? -1 : 0);
}
 
P uv(P u, P v) {
    return { v[0] - u[0],v[1] - u[1] };
}
P add(P u, P v) {
    return { u[0] + v[0],u[1] + v[1] };
}
int dis2(P u, P v) {
    return (u[0] - v[0]) * (u[0] - v[0]) + (u[1] - v[1]) * (u[1] - v[1]);
}

int cross(P u, P v) {
    return u[0] * v[1] - u[1] * v[0];
}
 
int dot(P u, P v) {
    return u[0] * v[0] + u[1] * v[1];
}
 
int loca(P u, P v, P w) {
    return sgn(cross(uv(u, v), uv(u, w)));
}
int locb(P u, P v, P w) {
    return sgn(dot(uv(u, v), uv(u, w)));
}
 
struct argcmp {//极角排序
    inline static int DS[4] = { 1,2,4,3 };
    bool operator()(const P& a, const P& b)const {
        const auto quad = [&](const P& u) {
            return DS[(sgn(u[1]) < 0) * 2 + (sgn(u[0]) < 0)];
            };
        int c = quad(a), d = quad(b);
        if (c != d) return c < d;
        return sgn(cross(a, b)) > 0;
    }
};
 
PD rotate(P l, double angle) {//逆时针旋转angle
    ld cosa = cos(angle), sina = sin(angle);
    return { l[0] * cosa - l[1] * sina, l[0] * sina + l[1] * cosa };
}
 
int point_on_segment(P a, LI line) {
    return sgn(cross(uv(a, line[0]), uv(a, line[1]))) == 0
        && sgn(dot(uv(a, line[0]), uv(a, line[1]))) <= 0;
}
 
bool inter_judge_segment(LI a, LI b) {
    //一个点的端点在另一个线段
    if (point_on_segment(b[0], a)
        || point_on_segment(b[1], a)
        || point_on_segment(a[0], b)
        || point_on_segment(a[1], b))
        return 1;
    //跨立试验
    return (loca(a[0], b[0], a[1]) * loca(a[0], b[1], a[1]) < 0
        && loca(b[0], a[0], b[1]) * loca(b[0], a[1], b[1]) < 0
        );
}
 
 
bool inter_judge(LI a, LI b) {
    return sgn(cross(uv(a[0], a[1]), uv(a[0], b[0]))
        - cross(uv(a[0], a[1]), uv(a[0], b[1]))) != 0;
}
PD line_inter(LI a, LI b) {
    ld s1 = cross(uv(a[0], a[1]), uv(a[0], b[0]));
    ld s2 = cross(uv(a[0], a[1]), uv(a[0], b[1]));
    return (PD{ (s2 * b[0][0] - s1 * b[1][0]) / (s2 - s1),
        (s2 * b[0][1] - s1 * b[1][1]) / (s2 - s1) });
}
 
vector<P> convex_hull(vector<P> a) {//Andrew求凸包(扫描线)
    if (a.size() <= 2) return a;
    sort(a.begin(), a.end());
    vector<P> ret;
    for (int i = 0;i < a.size();i++) {
        while (ret.size() >= 2 && loca(ret[ret.size() - 2], ret[ret.size() - 1], a[i]) <= 0)
            ret.pop_back();
        ret.push_back(a[i]);
    }
    int fixed = ret.size();
    for (int i = (int)a.size() - 2;i >= 0;i--) {
        while (ret.size() > fixed && loca(ret[ret.size() - 2], ret[ret.size() - 1], a[i]) <= 0)
            ret.pop_back();
        ret.push_back(a[i]);
    }
    ret.pop_back();
    return ret;
}
array<int, 2> in_convex(P p, const CI& a) {//{no | strictly yes | yes,where}
    int n = a.size();
    if (n == 1) {
        return { sgn(p[0] - a[0][0]) == 0 && sgn(p[1] - a[0][0]) == 0,0 };
    }
    if (n == 2) {
        return { point_on_segment(p, { a[0],a[1] }),0 };
    }
    int l = 1, r = n - 2;
    while (l <= r) {
        int mid = l + r >> 1;
        int u = loca(a[0], a[mid], p);
        int v = loca(a[0], a[mid + 1], p);
        if (u >= 0 && v <= 0) {
            if (loca(a[mid], a[mid + 1], p) >= 0) {
                {//在凸包的边上
                    if (loca(a[mid], a[mid + 1], p) == 0) return { 2,mid };
                    if (mid == 1 && loca(a[mid], a[0], p) == 0) return { 2,0 };
                    if (mid + 1 == n - 1 && loca(a[mid + 1], a[0], p) == 0) return { 2,n - 1 };
                }
                return { 1,mid };
            }
            return { 0,0 };
        }
        if (u < 0) r = mid - 1;
        else l = mid + 1;
    }
    return { 0,0 };
}

int diam2(const CI& a) {//直径平方
    int r = 0;
    int n = a.size();
    if (n <= 2) {
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                r = max(r, dis2(a[i], a[j]));
        return r;
    }
    for (int i = 0, j = 1; i < n; i++) {
        while (
            cross(uv(a[i], a[next(i, n)]), uv(a[i], a[j]))
            - cross(uv(a[i], a[next(i, n)]), uv(a[i], a[next(j, n)])) <= 0
            ) j = next(j, n);
        r = max({ r, dis2(a[i], a[j]), dis2(a[next(i, n)], a[j]) });
    }
    return r;
}
int area2(const vector<P>& a) {
    int ret = 0;
    for (int i = 0;i < a.size();i++) {
        int j = (i + 1) % a.size();
        ret += cross(a[i], a[j]);
    }
    return abs(ret);
}
 
P find_max(const CI& a, auto cmp) {//极点
    int l = 1, r = (int)a.size() - 2;
    if (cmp(a.back(), a[0])) {
        while (l <= r) {
            int mid = l + r >> 1;
            if (cmp(a[l - 1], a[mid]) && cmp(a[mid - 1], a[mid])) l = mid + 1;
            else r = mid - 1;
        }
        return a[r];
    }
    else {
        while (l <= r) {
            int mid = l + r >> 1;
            if (cmp(a[r + 1], a[mid]) && cmp(a[mid + 1], a[mid])) r = mid - 1;
            else l = mid + 1;
        }
        return a[l];
    }
}
 
//The order of the answer is counterclockwise of the convex hull.
array<P, 2> tangent(const CI& a, P u) {//过u的切线
    //如果点在凸包的点和边需要特判
    return { find_max(a,[&](auto x,auto y) {return loca(u,x,y) > 0;}),
            find_max(a,[&](auto x,auto y) {return loca(u,y,x) > 0;}) };
}
 
array<P, 2> tangent_vec(const CI& a, P u) {//与u平行的切线
    //如果点在凸包的点和边需要特判
    return { find_max(a,[&](auto x,auto y) {return sgn(cross(u,uv(x,y))) > 0;}),
            find_max(a,[&](auto x,auto y) {return sgn(cross(u,uv(y,x))) > 0;}) };
}
 
 
CI minkovski(vector<CI> C) {//结果是非严格凸包，即存在三点共线(可以通过再跑一遍凸包算法变成严格凸包)
    auto run = [&](array<CI, 2> a) {
        for (int i = 0;i < 2;i++) a[i].push_back(a[i].front());
        int i[2] = { 0,0 }, j[2] = { 0,0 }, len[2] = { (int)a[0].size() - 1,(int)a[1].size() - 1 };
        vector<P> ret;
        ret.push_back(add(a[0][0], a[1][0]));
        do {
            int d;
            if (!j[0] && !j[1]) {
                d = sgn(cross(uv(a[1][i[1]], a[1][i[1] + 1]),
                    uv(a[0][i[0]], a[0][i[0] + 1]))) >= 0;
            }
            else if (!j[0]) d = 0;
            else if (!j[1]) d = 1;
            else break;
            ret.push_back(add(uv(a[d][i[d]], a[d][i[d] + 1]), ret.back()));
            i[d] = (i[d] + 1) % len[d];
            if (i[d] == 0) j[d] = 1;
        } while (!j[0] || !j[1]);
        return ret;
        };
    for (auto& i : C) i = convex_hull(i);
    array<CI, 2> ret;ret[0] = C[0];
    for (int i = 1;i < C.size();i++) {
        ret[1] = C[i];
        ret[0] = run(ret);
    }
    return ret[0];
}

array<int, 2> cover(const vector<P>& a, const P& o) {//回转数法判断点是否在多边形内(O(n)),要求顺序是顺时针or逆时针
    int cnt = 0, n = a.size();//回转数=0表示在多边形外
    for (int i = 0; i < n; i++) {
        P u = a[i], v = a[next(i, n)];
        if (sgn(cross(uv(o, u), uv(o, v))) == 0 && sgn(dot(uv(o, u), uv(o, v))) <= 0) return { 1,1 };//在多边形上
        if (sgn(u[1] - v[1]) == 0) continue;
        if (sgn(u[1] - v[1]) < 0 && loca(u, v, o) <= 0) continue;
        if (sgn(u[1] - v[1]) > 0 && loca(u, v, o) >= 0) continue;
        if (sgn(u[1] - o[1]) < 0 && sgn(v[1] - o[1]) >= 0) cnt++;
        if (sgn(u[1] - o[1]) >= 0 && sgn(v[1] - o[1]) < 0) cnt--;
    }
    return { cnt,0 };//返回值表示回转数及是否在多边形一条边上
}


