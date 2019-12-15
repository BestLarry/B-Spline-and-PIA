#include "Vec.h"

Vec2D operator*(const Vec2D& v, double a)
{
    return { v.x * a, v.y * a };
}
Vec2D operator*(double a, const Vec2D& v)
{
    return { v.x * a, v.y * a };
}
Vec2D operator/(const Vec2D& v, double a)
{
    return { v.x / a, v.y / a };
}
Vec2D operator+(const Vec2D& v, const Vec2D& w)
{
    return { v.x + w.x,v.y + w.y };
}
Vec2D operator-(const Vec2D& v, const Vec2D& w)
{
    return { v.x - w.x,v.y - w.y };
}

Vec3D operator*(const Vec3D& v, double a)
{
    return { v.x * a, v.y * a, v.z * a };
}
Vec3D operator*(double a, const Vec3D& v)
{
    return { v.x * a, v.y * a, v.z * a };
}
Vec3D operator/(const Vec3D& v, double a)
{
    return { v.x / a, v.y / a, v.z / a };
}
Vec3D operator+(const Vec3D& v, const Vec3D& w)
{
    return { v.x + w.x,v.y + w.y, v.z + w.z };
}
Vec3D operator-(const Vec3D& v, const Vec3D& w)
{
    return { v.x - w.x,v.y - w.y, v.z - w.z };
}
