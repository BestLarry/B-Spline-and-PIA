#ifndef __PIA__
#define __PIA__
#include <vector>
#include "Vec.h"

/*
    PIA�㷨
    ������
        P��n����ϵĵ�
        B��n�����򻯵Ļ�
        t��n�����Ӧ�Ĳ���
        indexes��Ҫ�����ĵ���±꣬Ĭ��ȫ������
        error���������
        max_iter������������
    ����ֵ��
        n�����Ƶ�
*/
std::vector<Vec2D> CurvePIA(const std::vector<Vec2D>& P,
    const std::vector<Base>& B, const std::vector<double>& t,
    double error = 1e-5, size_t max_iter = 1000);

/*
    PIA�㷨
    ������
        P��n*m����ϵĵ�
        B1, B2�����򻯵Ļ�
        u, v����Ӧ�Ĳ���
        error���������
        max_iter������������
    ����ֵ��
        n*m�����Ƶ�
*/
std::vector<std::vector<Vec3D>> SurfacePIA(const std::vector<std::vector<Vec3D>>& P,
    const std::vector<Base>& B1, const std::vector<Base>& B2,
    const std::vector<double>& u, const std::vector<double>& v,
    double error = 1e-5, size_t max_iter = 1000);
#endif // !__PIA__
