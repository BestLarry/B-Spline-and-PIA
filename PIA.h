#ifndef __PIA__
#define __PIA__
#include <vector>
#include "Vec.h"

/*
    PIA算法
    参数：
        P：n个拟合的点
        B：n个正则化的基
        t：n个点对应的参数
        indexes：要调整的点的下标，默认全部调整
        error：误差，无穷范数
        max_iter：最大迭代次数
    返回值：
        n个控制点
*/
std::vector<Vec2D> CurvePIA(const std::vector<Vec2D>& P,
    const std::vector<Base>& B, const std::vector<double>& t,
    double error = 1e-5, size_t max_iter = 1000);

/*
    PIA算法
    参数：
        P：n*m个拟合的点
        B1, B2：正则化的基
        u, v：对应的参数
        error：误差，无穷范数
        max_iter：最大迭代次数
    返回值：
        n*m个控制点
*/
std::vector<std::vector<Vec3D>> SurfacePIA(const std::vector<std::vector<Vec3D>>& P,
    const std::vector<Base>& B1, const std::vector<Base>& B2,
    const std::vector<double>& u, const std::vector<double>& v,
    double error = 1e-5, size_t max_iter = 1000);
#endif // !__PIA__
