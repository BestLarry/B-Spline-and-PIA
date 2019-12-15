#ifndef __VEC__
#define __VEC__
#include <functional>

typedef std::function<double(double)> Base;

struct Vec2D
{
    double x;
    double y;

    friend Vec2D operator*(const Vec2D& v, double a);
    friend Vec2D operator*(double a, const Vec2D& v);
    friend Vec2D operator/(const Vec2D& v, double a);
    friend Vec2D operator+(const Vec2D& v, const Vec2D& w);
    friend Vec2D operator-(const Vec2D& v, const Vec2D& w);
    Vec2D operator+=(const Vec2D& w)
    {
        *this = *this + w;
        return *this;
    }
    Vec2D operator-=(const Vec2D& w)
    {
        *this = *this - w;
        return *this;
    }
};

struct Vec3D
{
    double x;
    double y;
    double z;

    friend Vec3D operator*(const Vec3D& v, double a);
    friend Vec3D operator*(double a, const Vec3D& v);
    friend Vec3D operator/(const Vec3D& v, double a);
    friend Vec3D operator+(const Vec3D& v, const Vec3D& w);
    friend Vec3D operator-(const Vec3D& v, const Vec3D& w);
    Vec3D operator+=(const Vec3D& w)
    {
        *this = *this + w;
        return *this;
    }
    Vec3D operator-=(const Vec3D& w)
    {
        *this = *this - w;
        return *this;
    }
};

#endif // !__VEC__
