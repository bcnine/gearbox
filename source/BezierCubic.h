#ifndef BEZIER_CUBIC
#define BEZIER_CUBIC

#include "Vector.h"

namespace gbox
{

class BezierCubic
{
public:
    BezierCubic (const Vec3d &p0, const Vec3d &p1, const Vec3d &p2, const Vec3d &p3);

    Vec3d evaluate (double t);

private:
    const Vec3d m_p0, m_p1, m_p2, m_p3;
};

};

#endif
