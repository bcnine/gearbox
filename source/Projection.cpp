#include "Projection.h"

#include "Constants.h"

namespace gbox
{

void
Projection::fit2DWindow(GLsizei vieww, GLsizei viewh, GLdouble &l, GLdouble &r, GLdouble &b, GLdouble &t)
{
	double winw = r-l;
	double winh = t-b;
	double viewasp = double(vieww)/viewh;

	if (winw/winh > viewasp)
	{
		double c = (b+t)/2;
		double halfwinh = winw/(viewasp*2);
		b = c-halfwinh;
		t = c+halfwinh;
	}
	else
	{
		double c = (l+r)/2;
		double halfwinw = (winh*viewasp)/2;
		l = c-halfwinw;
		r = c+halfwinw;
	}
}

Mat4d
Projection::ortho2D(GLdouble l, GLdouble r, GLdouble b, GLdouble t)
{
	return ortho(l, r, b, t, -1, 1);
}

Mat4d
Projection::ortho(GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f)
{
	return Mat4d(2/(r-l), 0,       0,       -(r+l)/(r-l),
	             0,       2/(t-b), 0,       -(t+b)/(t-b),
	             0,       0,       2/(n-f), (n+f)/(n-f),
	             0,       0,       0,       1);
}

Mat4d
Projection::frustum(GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f)
{
	return Mat4d(2*n/(r-l), 0,         (r+l)/(r-l),  0,
	             0,         2*n/(t-b), (t+b)/(t-b),  0,
	             0,         0,         -(f+n)/(f-n), -2*f*n/(f-n),
	             0,         0,         -1,           0);
}

Mat4d
Projection::perspective(GLdouble vfov, GLdouble aspect, GLdouble n, GLdouble f)
{
	GLdouble t, b, r, l;
	perspective2DWindow(vfov, aspect, n, t, b, r, l);

	return frustum(l, r, b, t, n, f);
}

void
Projection::perspective2DWindow(GLdouble vfov, GLdouble aspect, GLdouble n,
                                GLdouble &l, GLdouble &r, GLdouble &b, GLdouble &t)
{
	t = n*tan((s_torad*(vfov/2)));
	b = -t;
	r = t*aspect;
	l = -r;
}

bool
Projection::unproject(const Vec3d &winp,
                      const Mat4d &modelmat,
					  const Mat4d projmat,
					  const Vec4i &viewport,
					  Vec3d &objp)
{
	Mat4d mvpi(inverse(projmat * modelmat));

    GLdouble inx = 2*(winp.x() - viewport[0])/viewport[2] - 1;
    GLdouble iny = 2*(winp.y() - viewport[1])/viewport[3] - 1;
    GLdouble inz = 2*winp.z() - 1;

	Vec4d out(mvpi * Vec4d(inx, iny, inz, 1.0));
	if (out[3] == 0.0)
		return false;

	out /= out[3];
    objp.x() = out[0];
    objp.y() = out[1];
    objp.z() = out[2];

	return true;
}

};
