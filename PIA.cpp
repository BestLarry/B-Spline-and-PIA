#include <limits>
#include <math.h>
#include <algorithm>
#include "PIA.h"

using namespace std;

/*
    生成曲线上参数为t的点
*/
inline std::vector<Vec2D> Curve(const std::vector<Vec2D>& P, const std::vector<Base>& B, const std::vector<double> t)
{
    vector<Vec2D> ret(t.size(), { 0,0 });
    for (size_t i = 0; i < t.size(); i++)
    {
        for (size_t j = 0; j < P.size(); j++)
        {
            ret[i] += B[j](t[i]) * P[j];
        }
    }
    return ret;
}

/*
    计算误差向量的无穷范数
*/
inline double Error(const std::vector<Vec2D>& P, const std::vector<Vec2D>& Q)
{
    double ret = numeric_limits<double>::min();
    for (size_t i = 0; i < P.size(); i++)
    {
        double dist = sqrt(pow(P[i].x - Q[i].x, 2) + pow(P[i].y - Q[i].y, 2));
        ret = max(ret, dist);
    }
    return ret;
}

/*
    PIA算法
    参数：
        P：n个拟合的点
        B：n个基
        t：n个点对应的参数
        error：误差，无穷范数
        max_iter：最大迭代次数
    返回值：
        n个控制点
*/
std::vector<Vec2D> CurvePIA(const std::vector<Vec2D>& P,
    const std::vector<Base>& B, const std::vector<double>& t,
    double error, size_t max_iter)
{
    vector<Vec2D> Q = P;  // 控制点
    for (size_t iter = 0; iter < max_iter; iter++)
    {
        vector<Vec2D> C = Curve(Q, B, t);  // 曲线上的点
        // 检测误差
        double err = Error(P, C);
        if (err < error)
            break;
        // 更新控制点
        for (size_t i = 0; i < Q.size(); i++)
        {
            Q[i] += P[i] - C[i];
        }
    }
    return Q;
}

/*
    生成曲面上参数在u、v的点
*/
inline std::vector<std::vector<Vec3D>> Surface(const std::vector<std::vector<Vec3D>>& P,
    const std::vector<Base>& B1, const std::vector<Base>& B2,
    const std::vector<double>& u, const std::vector<double>& v)
{
    vector<vector<Vec3D>> ret(u.size(), vector<Vec3D>(v.size(), { 0,0,0 }));
    for (size_t i = 0; i < u.size(); i++)
    {
        for (size_t j = 0; j < v.size(); j++)
        {
            for (size_t p = 0; p < u.size(); p++)
            {
                for (size_t q = 0; q < v.size(); q++)
                {
                    ret[i][j] += P[p][q] * B1[p](u[i]) * B2[q](v[j]);
                }
            }
        }
    }
    return ret;
}

/*
    计算误差向量的无穷范数
*/
inline double Error(const std::vector<std::vector<Vec3D>>& P, const std::vector<std::vector<Vec3D>>& Q)
{
    double ret = numeric_limits<double>::max();
    for (size_t i = 0; i < P.size(); i++)
    {
        for (size_t j = 0; j < P.front().size(); j++)
        {
            double dist = sqrt(pow(P[i][j].x - Q[i][j].x, 2) + pow(P[i][j].y - Q[i][j].y, 2) + pow(P[i][j].z - Q[i][j].z, 2));
            ret = min(ret, dist);
        }
    }
    return ret;
}

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
    double error, size_t max_iter)
{
    vector<vector<Vec3D>> Q = P;  // 控制点
    for (size_t iter = 0; iter < max_iter; iter++)
    {
        vector<vector<Vec3D>> C = Surface(Q, B1, B2, u, v);  // 曲线上的点
        // 检测误差
        double err = Error(P, C);
        if (err < error)
            break;
        // 更新控制点
        for (size_t i = 0; i < Q.size(); i++)
        {
            for (size_t j = 0; j < Q.front().size(); j++)
            {
                Q[i][j] += P[i][j] - C[i][j];
            }
        }
    }
    return Q;
}