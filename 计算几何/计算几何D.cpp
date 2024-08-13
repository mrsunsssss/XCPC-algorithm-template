#define debugP(x) cerr<<#x<<":("<<x[0]<<','<<x[1]<<")"<<endl
using ld = long double;
using P = array<int, 2>;
using PD = array<ld, 2>;
using LI = array<P, 2>;
using LD = array<PD, 2>;
const ld eps = 1e-9;

namespace Geometry_D {
    int sgn(ld x) {
        return x > eps ? 1 : (x < -eps ? -1 : 0);
    }
    PD uv(PD u, PD v) {
        return { v[0] - u[0],v[1] - u[1] };
    }
    ld cross(PD u, PD v) {
        return u[0] * v[1] - u[1] * v[0];
    }
    ld dot(PD u, PD v) {
        return u[0] * v[0] + u[1] * v[1];
    }
    ld dis(PD u, PD v) {
        return sqrt((u[0] - v[0]) * (u[0] - v[0]) + (u[1] - v[1]) * (u[1] - v[1]));
    }

    PD mul(PD p, ld x) {
        return { p[0] * x,p[1] * x };
    }

    PD add(PD u, PD v) {
        return { u[0] + v[0],u[1] + v[1] };
    }

    PD div(PD p, ld x) {
        return { p[0] / x,p[1] / x };
    }

    PD project(LD l, PD p) {
        PD base = uv(l[0], l[1]);//两点式描述直线
        ld r = dot(uv(l[0], p), base) / (base[0] * base[0] + base[1] * base[1]);
        return add(l[0], mul(base, r));
    }

    int point_on_segment(PD a, LD line) {
        return sgn(cross(uv(a, line[0]), uv(a, line[1]))) == 0
            && sgn(dot(uv(a, line[0]), uv(a, line[1]))) <= 0;
    }
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
};
using namespace Geometry_D;
