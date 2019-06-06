#include "BezierCubic.h"

#include "Vector.h"

namespace gbox
{

BezierCubic::BezierCubic(const Vec3d &p0, const Vec3d &p1, const Vec3d &p2, const Vec3d &p3) :
m_p0(p0),
m_p1(p1),
m_p2(p2),
m_p3(p3)
{
}

Vec3d
BezierCubic::evaluate(double s)
{
    Vec3d q1((1-s)*m_p0 + s*m_p1);
    Vec3d q2((1-s)*q1 + s*((1-s)*m_p1 + s*m_p2));

    Vec3d r2((1-s)*m_p2 + s*m_p3);
    Vec3d r1((1-s)*((1-s)*m_p1 + s*m_p2) + s*r2);

    return (1-s)*q2 + s*r1;
}

}
