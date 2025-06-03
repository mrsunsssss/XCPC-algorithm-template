//mt19937 rng(random_device{}());
namespace SimulateAnneal {//模拟退火
    const ld MAX_TIME = 0.8;
    const ld EPS = 1e-14;
    ld RES;//最终答案
    ld RAND() { return rand() * 2 - RAND_MAX; }//随机函数
    //ld __RAND() { return 2ll * rng() - mt19937::max(); }//随机函数
    ld calc(ld x, ld y, ld z) {//所求函数

    }
    ld x, y, z;//函数的参数
    void SimulateAnneal() {
        ld T = 1e5;//初始温度
        const ld T0 = 0.9982;//降温速度
        while (T > EPS) {
            ld nx = x + RAND() * T;
            ld ny = y + RAND() * T;
            ld nz = z + RAND() * T;
            ld nRES = calc();
            ld delta = nRES - RES;
            if (delta < 0) {//更优则接受
                x = nx, y = ny, z = nz;
                RES = nRES;
            }
            else if (exp(-delta / T) * RAND_MAX > rand()) {//否则概率接受
                x = nx, y = ny, z = nz;
            }
            T = T * T0;
        }
    }

    void run() {
        RES = 1e100;
        for (int i = 1;i <= 5;i++) SimulateAnneal();
        //while ((double)clock() / CLOCKS_PER_SEC < MAX_TIME) SimulateAnneal();
    }
}
using namespace SimulateAnneal;
//srand(99999989);
