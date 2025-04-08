#define debugP(x) cerr<<#x<<":("<<x[0]<<','<<x[1]<<")"<<endl
using PI = array<int, 2>;
using VI = array<int, 2>;
using LI = array<PI, 2>;
using CI = vector<PI>;

using ld = long double;
using PD = array<ld, 2>;
using VD = array<ld, 2>;
using LD = array<PD, 2>;
using CD = vector<PD>;
const ld eps = 1e-9;

using ty_g = int;
using P = PI;
using V = VI;
using L = LI;
using C = CI;

namespace Tools {
    int prev(int i, int n) { return i == 0 ? n - 1 : i - 1; }
    int next(int i, int n) { return i == n - 1 ? 0 : i + 1; }

    //int
    int sgn(int x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }
    VI uv(PI u, PI v) { return { v[0] - u[0],v[1] - u[1] }; }
    VI add(VI u, VI v) { return { u[0] + v[0],u[1] + v[1] }; }
    int dis2(PI u, PI v) { return (u[0] - v[0]) * (u[0] - v[0]) + (u[1] - v[1]) * (u[1] - v[1]); }
    int cross(VI u, VI v) { return u[0] * v[1] - u[1] * v[0]; }//角度，顺逆时针，sin，三角形面积
    int dot(VI u, VI v) { return u[0] * v[0] + u[1] * v[1]; }//投影，cos，余弦相似度
    int loca(PI u, PI v, PI w) { return sgn(cross(uv(u, v), uv(u, w))); }
    int locb(PI u, PI v, PI w) { return sgn(dot(uv(u, v), uv(u, w))); }
    int point_equal(PI u, PI v) { return u[0] == v[0] and u[1] == v[1]; }
    VI rotate_90(VI l) { return { -l[1], l[0] }; }

    //double
    ld sgn(ld x) { return x > eps ? 1 : (x < -eps ? -1 : 0); }
    VD uv(PD u, PD v) { return { v[0] - u[0],v[1] - u[1] }; }
    ld cross(PD u, PD v) { return u[0] * v[1] - u[1] * v[0]; }
    ld dot(PD u, PD v) { return u[0] * v[0] + u[1] * v[1]; }
    ld dis(PD u, PD v) { return sqrt((u[0] - v[0]) * (u[0] - v[0]) + (u[1] - v[1]) * (u[1] - v[1])); }
    ld dis2(PD u, PD v) { return ((u[0] - v[0]) * (u[0] - v[0]) + (u[1] - v[1]) * (u[1] - v[1])); }
    VD mul(VD p, ld x) { return { p[0] * x,p[1] * x }; }
    VD add(VD u, VD v) { return { u[0] + v[0],u[1] + v[1] }; }
    VD sub(VD u, VD v) { return { u[0] - v[0],u[1] - v[1] }; }
    VD div(VD p, ld x) { return { p[0] / x,p[1] / x }; }
    int loca(PD u, PD v, PD w) { return sgn(cross(uv(u, v), uv(u, w))); }
    PD project(LD l, PD p) {
        VD base = uv(l[0], l[1]);//两点式描述直线
        ld r = dot(uv(l[0], p), base) / (base[0] * base[0] + base[1] * base[1]);
        return add(l[0], mul(base, r));
    }
    VD rotate(VD l, ld angle) {//逆时针旋转angle
        //x=rcosa,y=rsina;x'=rcos(a+b)=rcosa*cosb-rsina*sinb=xcosb-ysinb,y'=rsin(a+b)=rsina*cosb+rcosa*sinb=xsinb+ycosb
        ld cosa = cos(angle), sina = sin(angle);
        return { l[0] * cosa - l[1] * sina, l[0] * sina + l[1] * cosa };
    }
    VD rotate_90(VD l) { return { -l[1], l[0] }; }
    int greater_equal_to(ld x, ld y) { return x + eps >= y; }//x>y or equal_to(x,y)
    int less_equal_to(ld x, ld y) { return x <= y + eps; }//x<y or equal_to(x,y)
    int equal_to(ld x, ld y) { return abs(x - y) <= eps; }
    int point_equal(PD u, PD v) { return equal_to(u[0], v[0]) and equal_to(u[1], v[1]); }
    ld calc_angle_dif(P u, P v) {//[0,2*Pi)
        auto a = atan2(cross(u, v), dot(u, v));/*arctan(uv*sin/uv*cos)*/
        return a < 0 ? a + 2 * Pi : a;
    }
    ld calc_angle(P u) {//ou与ox坐标轴的夹角.[0,2*Pi),推荐直接用atan2
        auto a = atan2(u[1], u[0]);//(-Pi,Pi]
        return a < 0 ? a + 2 * Pi : a;
    }

    //int -> double
    ld convert(int x) { return static_cast<ld>(x); }//int -> ld
    PD convert(const PI& a) { return PD{ convert(a[0]), convert(a[1]) }; }// PI -> PD
    LD convert(const LI& a) { return LD{ convert(a[0]), convert(a[1]) }; }// LI -> LD
    CD convert(const CI& a) {// CI -> CD
        CD res;res.reserve(a.size());
        for (const auto& p : a) res.push_back(convert(p));
        return res;
    }
}

namespace Segments {
    using namespace Tools;
    bool point_on_segment(P a, L line) {
        return sgn(cross(uv(a, line[0]), uv(a, line[1]))) == 0
            && sgn(dot(uv(a, line[0]), uv(a, line[1]))) <= 0;
    }
    bool inter_judge_segment(L a, L b) {
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
}

namespace Lines {
    using namespace Tools;
    PD line_inter(LD a, LD b) {//两点式，要求直线不平行
        VD v1 = uv(a[0], a[1]), v2 = uv(b[0], b[1]);
        return add(a[0], mul(v1, cross(v2, uv(b[0], a[0])) / cross(v1, v2)));
    }
    bool inter_judge(L a, L b) {
        return sgn(cross(uv(a[0], a[1]), uv(a[0], b[0]))
            - cross(uv(a[0], a[1]), uv(a[0], b[1]))) != 0;
    }
}

namespace Circles {
    using namespace Tools;using namespace Lines;
    array<PD, 2> inter_circle_line(PD o, ld r, LD line) {
        PD s = line[0], t = line[1];
        PD pr = project(line, o);
        ld d = dis(o, pr);
        if (sgn(d - r) > 0) return { nan(""),nan("") };//use isnan(x) to check
        ld len = sqrt(r * r - d * d);
        PD dir = div(uv(s, t), dis(s, t));
        PD inter1 = add(pr, mul(dir, len));
        PD inter2 = add(pr, mul(dir, -len));
        return { inter1,inter2 };
    }
    pair<PD, ld> make_circle(const PD& a, const PD& b) {
        PD o = mul(add(a, b), 0.5);
        ld r = dis(o, a);
        return pair<PD, ld> {o, r};
    }
    pair<PD, ld> make_circle(const PD& a, const PD& b, const PD& c) {//三角形外接圆（任取三角形两边中垂线的交点）
        PD A = mul(add(b, c), 0.5), B = mul(add(a, c), 0.5);
        VD x = rotate_90(uv(A, c));
        VD y = rotate_90(uv(B, c));
        PD o = line_inter({ A,add(A,x) }, { B,add(B,y) });
        ld r = dis(o, a);
        return pair<PD, ld> {o, r};
    }
}

namespace Convex_Hull {
    using namespace Tools;using namespace Segments;
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
    //0:在外面, 1:在边上, 2:在内部 
    int in_convex(P p, const C& a) {//二分检查p是否在a[i],a[i+1],a[0]形成的三角形上
        int n = a.size();
        if (a.size() == 1) return point_equal(p, a[0]);
        if (a.size() == 2) return point_on_segment(p, { a[0],a[1] });
        if (point_equal(a[0], p)) return 1;//在a[0]上
        if (loca(a[0], a[1], p) < 0 or loca(a[0], a.back(), p) > 0) return 0;
        if (loca(a[1], a[0], p) == 0) return 1;//在a[0]和a[1]的边上
        if (loca(a[n - 1], a[0], p) == 0) return 1;//在a[0]和a[n-1]的边上
        int l = 1, r = n - 2;
        while (l <= r) {
            int mid = l + r >> 1;
            int u = loca(a[0], a[mid], p);
            int v = loca(a[0], a[mid + 1], p);
            if (u >= 0 && v <= 0) {
                int t = loca(a[mid], a[mid + 1], p);
                if (t == 0) return 1;//在a[mid]和a[mid+1]的边上
                else if (t > 0) return 2;//在a[0],a[mid],a[mid+1]的三角形内部
                return 0;
            }
            if (u < 0) r = mid - 1;
            else l = mid + 1;
        }
        return 0;
    }

    ty_g diam2(const C& a) {//直径平方
        ty_g r = 0;
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
    ty_g area2(const vector<P>& a) {
        ty_g ret = 0;
        for (int i = 0;i < a.size();i++) {
            int j = (i + 1) % a.size();
            ret += cross(a[i], a[j]);
        }
        return abs(ret);
    }

    ld smallest_Rectangle_Cover(const CD& a) {//最小矩形覆盖
        int n = a.size();
        if (n <= 2) return 0;
        ld res = 4e18;
        int ans_i, ans_j, ans_l, ans_r;//凸包与矩形的四个切点
        for (int i = 0, j = 1, r = 1, l;i < n;i++) {
            VD vec = uv(a[i], a[next(i, n)]);
            while (sgn(
                cross(vec, uv(a[i], a[next(j, n)])) -
                cross(vec, uv(a[i], a[j]))
            ) >= 0) {
                j = next(j, n);
            }
            while (sgn(
                dot(vec, uv(a[i], a[next(r, n)])) -
                dot(vec, uv(a[i], a[r]))
            ) >= 0) {
                r = next(r, n);
            }
            if (i == 0) l = r;
            while (sgn(
                dot(vec, uv(a[i], a[next(l, n)])) -
                dot(vec, uv(a[i], a[l]))
            ) <= 0) {
                l = next(l, n);
            }
            ld H = abs(cross(vec, uv(a[i], a[j])));         // 少除了dis
            ld B1 = abs(dot(vec, uv(a[i], a[l])));          // 少除了dis
            ld B2 = abs(dot(vec, uv(a[next(i, n)], a[r]))); // 少除了dis
            ld B3 = dis2(a[i], a[next(i, n)]);              // 少除了dis
            ld cur = (B1 + B2 + B3) * H / dis2(a[i], a[next(i, n)]); // 减少精度误差，统一放到这里来除以dis2.
            if (cur < res) {
                res = cur;
                ans_i = i, ans_j = j, ans_l = l, ans_r = r;
            }
        }
        return res;
    }

    P find_max(const C& a, auto cmp) {//极点
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
    array<P, 2> tangent(const C& a, P u) {//过u的切线
        //如果点在凸包的点和边需要特判
        return { find_max(a,[&](auto x,auto y) {return loca(u,x,y) > 0;}),
                find_max(a,[&](auto x,auto y) {return loca(u,y,x) > 0;}) };
    }

    array<P, 2> tangent_vec(const C& a, P u) {//与u平行的切线
        //如果点在凸包的点和边需要特判
        return { find_max(a,[&](auto x,auto y) {return sgn(cross(u,uv(x,y))) > 0;}),
                find_max(a,[&](auto x,auto y) {return sgn(cross(u,uv(y,x))) > 0;}) };
    }


    C minkovski(vector<C> A) {//结果是非严格凸包，即存在三点共线(可以通过再跑一遍凸包算法变成严格凸包)
        auto run = [&](array<C, 2> a) {
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
        for (auto& i : A) i = convex_hull(i);
        array<C, 2> ret;ret[0] = A[0];
        for (int i = 1;i < A.size();i++) {
            ret[1] = A[i];
            ret[0] = run(ret);
        }
        return ret[0];
    }
}

namespace Dynamic_Convex_Hull {
    using namespace Tools;
    auto __compare = [](P u, P v) {return u[0] < v[0];};
    using SET = set<P, decltype(__compare)>;
    struct dynamic_convex_hull :SET {
        auto pre(iterator it) { return --it; }
        auto nxt(iterator it) { return ++it; }
        bool is_up;//上凸包还是下凸包
        dynamic_convex_hull(bool x) :is_up(x) {}
        int in_convex(P u) {
            auto it = lower_bound(u);
            if (it == end()) return 0;
            if (sgn(it->at(0) - u[0]) == 0) {
                return is_up ? sgn(it->at(1) - u[1]) >= 0 : sgn(it->at(1) - u[1]) <= 0;
            }
            if (it == begin()) return 0;
            P nxt_u = *it, pre_u = *pre(it);
            int t = loca(pre_u, u, nxt_u);
            return is_up ? t >= 0 : t <= 0;
        }
        int check_remove(SET::iterator it) {
            if (it == begin()) return 0;
            auto itl = pre(it);
            auto itr = nxt(it);
            if (itr == end()) return 0;
            int t = loca(*itl, *it, *itr);
            if (is_up ? t < 0 : t > 0) return 0;
            return erase(it), 1;
        }
        void push(P u) {
            if (in_convex(u)) return;
            auto it = find(u);
            if (it != end()) erase(it);
            it = insert(u).first;//set.insert={iterator,bool}
            while (it != begin() && check_remove(pre(it)));
            while (nxt(it) != end() && check_remove(nxt(it)));
        }
    };
}

namespace Polygon {
    using namespace Tools;

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
}

namespace Other {
    using namespace Tools;
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
    struct _argcmp {//直接计算角度极角排序，可能有误差
        bool operator()(const P& a, const P& b)const {
            return calc_angle(a) < calc_angle(b);
        }
    };
}

using namespace Tools;
using namespace Segments;
using namespace Lines;
using namespace Circles;
using namespace Convex_Hull;
using namespace Dynamic_Convex_Hull;
using namespace Polygon;
using namespace Other;
