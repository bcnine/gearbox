#define NOMINMAX
#include "Viewer.h"
#include "Constants.h"
#include "Projection.h"

#include <assert.h>
#include <algorithm>

namespace gbox
{

Viewer::Viewer() :
m_initial(true),
m_prevwinw(0),
m_prevwinh(0),
m_boxmin(Vec2d(0.0,0.0)),
m_boxmax(Vec2d(0.0,0.0)),
m_accel(0.0),
m_vel(0.0),
m_accelkeys(0),
m_accelkey(0),
m_velweight(10.0),
m_maxaccel(1.0),
m_maxvel(1.0)
{
	m_view.setIdentity();
}

Mat4d
Viewer::getViewMatrix() const
{
	return m_view;
}

Mat4d
Viewer::getProjMatrix() const
{
	return m_proj;
}

Mat4d
Viewer::lookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
               GLdouble centerx, GLdouble centery, GLdouble centerz,
               GLdouble upx, GLdouble upy, GLdouble upz)
{
	Vec3d n(eyex-centerx, eyey-centery, eyez-centerz);
	n.normalize();
	Vec3d u(Vec3d(upx, upy, upz) % n);
	u.normalize();
	Vec3d v(n % u);
	Vec3d eye(eyex, eyey, eyez);

	return Mat4d(u[0], u[1], u[2], u * -eye,
	             v[0], v[1], v[2], v * -eye,
	             n[0], n[1], n[2], n * -eye,
	             0,    0,    0,    1);
}

void
Viewer::unproject(const Vec3d &winp, Vec3d &objp)
{
	bool result = Projection::unproject(winp, m_view, m_proj, m_viewport, objp);
	assert(result);
}

void
Viewer::setViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	m_viewport.set(0, 0, width, height);
	glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
}

void
Viewer::setMaxVelocity(double velocity)
{
	m_maxvel = velocity;
}

void
Viewer::setMaxAcceleration(double acceleration)
{
	m_maxaccel = acceleration;
}

void
Viewer::setVelocityAttenuation(double attenuation)
{
	m_velweight = attenuation;
}

void
LandscapeViewer::setPosition(const Vec3d &pos)
{
	m_pos = pos;
	updateAll();
}

void
LandscapeViewer::setOrientation(const Vec3d &hpr)
{
	m_hpr = hpr;
	updateAll();
}

Vec3d
LandscapeViewer::getPosition () const
{
	return m_pos;
}

Vec3d
LandscapeViewer::getOrientation () const
{
	return m_hpr;
}

LandscapeViewer::LandscapeViewer() :
m_pos(0.0f, 0.0f, 0.0f),
m_hpr(0.0f, 0.0f, 0.0f),
m_nearclip(0.0),
m_farclip(0.0)
{
	updateAll();
}

void
LandscapeViewer::updateAll()
{
	updateDir();
	computeMatrices();
}

void
LandscapeViewer::updateDir()
{
	m_hpr[1] = std::min(88.0, m_hpr[1]);
	m_hpr[1] = std::max(-88.0, m_hpr[1]);

	if (m_hpr[0] < 0)
		m_hpr[0] += 360;
	if (m_hpr[0] >= 360)
		m_hpr[0] -= 360;

	double cphi = cos(s_torad*m_hpr[1]);
	double sphi = sin(s_torad*m_hpr[1]);
	double ctheta = cos(s_torad*m_hpr[0]);
	double stheta = sin(s_torad*m_hpr[0]);

	m_dir[0] = cphi*stheta;
	m_dir[1] = sphi;
	m_dir[2] = -cphi*ctheta;
	m_dir.normalize();
}

Mat4d
LandscapeViewer::setPerspective(GLdouble vfov, GLdouble aspect, GLdouble nearclip, GLdouble farclip)
{
	m_nearclip = nearclip;
	m_farclip = farclip;
	Projection::perspective2DWindow(vfov, aspect, nearclip, m_boxmin[0], m_boxmax[0], m_boxmin[1], m_boxmax[1]);
	m_proj = Projection::frustum(m_boxmin[0], m_boxmax[0], m_boxmin[1], m_boxmax[1], m_nearclip, m_farclip);

	return m_proj;
}

void
LandscapeViewer::computeMatrices()
{
	Vec3d pt(m_pos+m_dir);
	m_view = lookAt(m_pos[0],m_pos[1],m_pos[2],pt[0],pt[1],pt[2],0.0,1.0,0.0);
	m_proj = Projection::frustum(m_boxmin[0], m_boxmax[0], m_boxmin[1], m_boxmax[1], m_nearclip, m_farclip);
}

void
LandscapeViewer::windowResize(int winw, int winh)
{
	if (m_initial)
	{
		Projection::fit2DWindow(winw, winh, m_boxmin[0], m_boxmax[0], m_boxmin[1], m_boxmax[1]);
		m_initial = false;
	}
	else
	{
		double aspect = double(winw)/winh;
		double halfboxw = ((m_boxmax[0]-m_boxmin[0])*(double(winw)/m_prevwinw))/2;
		double wc = (m_boxmin[0]+m_boxmax[0])/2;
		m_boxmin[0] = wc-halfboxw;
		m_boxmax[0] = wc+halfboxw;

		double halfboxh = halfboxw/aspect;
		double hc = (m_boxmin[1]+m_boxmax[1])/2;
		m_boxmin[1] = hc-halfboxh;
		m_boxmax[1] = hc+halfboxh;
	}

	m_prevwinw = winw;
	m_prevwinh = winh;

	computeMatrices();
	setViewport(0, 0, winw, winh);
}

void
LandscapeViewer::motion(PointerButton btn, ButtonState s,
                        int prevx, int prevy, int x, int y)
{
	prevy = m_prevwinh - 1 - prevy;
	y = m_prevwinh - 1 - y;

	if (btn != LeftButton)
		return;

	int dx = x-prevx;
	int dy = y-prevy;
	if (dx)
		m_hpr[0] += 0.1f*dx;
	if (dy)
		m_hpr[1] += 0.1f*dy;

	updateAll();
}

void LandscapeViewer::timestep(double dt)
{
	if (m_accel > 0.0)
		m_vel += m_accel*dt;
	else
		m_vel -= m_velweight*m_vel*dt;

	if (m_vel > m_maxvel) m_vel = m_maxvel;
	if (m_vel < 0.001) m_vel = 0.0;

	m_pos += m_accel*getAccelerationVector()*m_vel*dt;

	computeMatrices();
}

void
LandscapeViewer::keyboardUp(unsigned char c, int x, int y)
{
	if (c == ' ')
		return;

	//if (--m_accelkeys <= 0)
	{
		m_accel = 0.0;
		m_accelkeys = 0;
	}
}

Vec3d
LandscapeViewer::getAccelerationVector()
{
	Vec3d accel;
	if (m_accelkey == 'w')
	{
		accel = m_dir;
	}
	else if (m_accelkey == 's')
	{
		accel = -m_dir;
	}
	else if (m_accelkey == 'd')
	{
		accel = unit(m_dir % Vec3d(0.0,1.0,0.0));
	}
	else if (m_accelkey == 'a')
	{
		accel = -unit(m_dir % Vec3d(0.0,1.0,0.0));
	}
	else if (m_accelkey == 'e')
	{
		Vec3d u(unit(m_dir % Vec3d(0.0,1.0,0.0)));
		accel = u % m_dir;
	}
	else if (m_accelkey == 'c')
	{
		Vec3d u(unit(m_dir % Vec3d(0.0,1.0,0.0)));
		accel = -(u % m_dir);
	}

	return accel;
}

void
LandscapeViewer::keyboard(unsigned char c, int x, int y)
{
	if (c == ' ')
	{
		m_hpr[0] += 180;
		m_hpr[1] *= -1.0f;
		updateDir();
		computeMatrices();
		return;
	}

	m_accel = m_maxaccel;
	m_accelkey = c;
	++m_accelkeys;
}

void
TopDownViewer::set2DWindow(double l, double r, double b, double t)
{
	m_boxmin[0] = l;
	m_boxmax[0] = r;
	m_boxmin[1] = b;
	m_boxmax[1] = t;
}

void
TopDownViewer::windowResize(int winw, int winh)
{
	if (m_initial)
	{
		Projection::fit2DWindow(winw, winh, m_boxmin[0], m_boxmax[0], m_boxmin[1], m_boxmax[1]);
		m_initial = false;
	}
	else
	{
		double aspect = double(winw)/winh;
		double halfboxw = ((m_boxmax[0]-m_boxmin[0])*(double(winw)/m_prevwinw))/2;
		double wc = (m_boxmin[0]+m_boxmax[0])/2;
		m_boxmin[0] = wc-halfboxw;
		m_boxmax[0] = wc+halfboxw;

		double halfboxh = halfboxw/aspect;
		double hc = (m_boxmin[1]+m_boxmax[1])/2;
		m_boxmin[1] = hc-halfboxh;
		m_boxmax[1] = hc+halfboxh;
	}

	m_prevwinw = winw;
	m_prevwinh = winh;

	computeMatrices();
	setViewport(0, 0, winw, winh);
}

void
TopDownViewer::setPosition(const Vec3d &pos)
{
	m_pos = pos;
	computeMatrices();
}

TopDownViewer::TopDownViewer() :
Viewer(),
m_pos(0.0f, 0.0f, 0.0f),
m_zoomin(true),
m_zoomx(0),
m_zoomy(0),
m_zoomaccel(0.0),
m_zoomvel(0.0),
m_zoomfac(0.01)
{
	setMaxVelocity(m_maxvel);
	setMaxAcceleration(m_maxaccel);
	setVelocityAttenuation(m_velweight);
	computeMatrices();
}

void
TopDownViewer::reset()
{
	m_pos = Vec3d(0.0, 0.0, 0.0);
	m_initial = true;
	windowResize(m_prevwinw, m_prevwinh);
}

void
TopDownViewer::computeMatrices()
{
	m_view = Mat4d(1.0, 0.0, 0.0, m_pos[0],
	               0.0, 1.0, 0.0, m_pos[1],
	               0.0, 0.0, 1.0, 0.0,
	               0.0, 0.0, 0.0, 1.0);

	m_proj = Projection::ortho2D(m_boxmin[0], m_boxmax[0], m_boxmin[1], m_boxmax[1]);
}

void
TopDownViewer::pointer(PointerButton button, ButtonState state, int x, int y)
{
	if (state == ButtonDown)
	{
		if (button == WheelUpButton)
		{
			zoom(true, x, y, m_zoomfac);
			computeMatrices();
		}
		else if (button == WheelDownButton)
		{
			zoom(false, x, y, m_zoomfac);
			computeMatrices();
		}
	}
}

Vec3d
TopDownViewer::getPosition() const
{
	return m_pos;
}

void
TopDownViewer::motion(PointerButton btn, ButtonState state, int prevx, int prevy, int x, int y)
{
	if (btn == LeftButton && state == ButtonDown)
	{
		Vec3d obj, pobj;

		bool result;
		result = Projection::unproject(Vec3d(x, y, 0.0), m_view, m_proj, m_viewport, obj);
		assert(result);
		result = Projection::unproject(Vec3d(prevx, prevy, 0.0), m_view, m_proj, m_viewport, pobj);
		assert(result);

		m_pos += obj-pobj;

		computeMatrices();
	}
}

void
TopDownViewer::setZoomFactor(double zoomfac)
{
	m_zoomfac = zoomfac;
}

void
TopDownViewer::zoom(bool in, int x, int y, double d)
{
	double zoom = in ? 1-d : 1/(1-d);

	bool result;
	result = Projection::unproject(Vec3d(x, y, 0.0), m_view, m_proj, m_viewport, m_pivot);
	assert(result);

	Mat4d t(1.0, 0.0, 0.0, -(m_pivot[0]+m_pos[0]),
	        0.0, 1.0, 0.0, -(m_pivot[1]+m_pos[1]),
	        0.0, 0.0, 1.0, 0.0,
	        0.0, 0.0, 0.0, 1.0);
	Mat4d s(zoom, 0.0, 0.0, 0.0,
	        0.0, zoom, 0.0, 0.0,
	        0.0, 0.0, 1.0, 0.0,
	        0.0, 0.0, 0.0, 1.0);
	Mat4d tinv(1.0, 0.0, 0.0, m_pivot[0]+m_pos[0],
	           0.0, 1.0, 0.0, m_pivot[1]+m_pos[1],
	           0.0, 0.0, 1.0, 0.0,
	           0.0, 0.0, 0.0, 1.0);
	Mat4d m(tinv*s*t);
	Vec4d p1(m_boxmin[0], m_boxmin[1], 0.0, 1.0);
	Vec4d p2(m_boxmax[0], m_boxmax[1], 0.0, 1.0);
	p1 = m * p1;
	p2 = m * p2;
	m_boxmin[0] = p1[0]; m_boxmin[1] = p1[1];
	m_boxmax[0] = p2[0]; m_boxmax[1] = p2[1];
}

void
TopDownViewer::timestep(double dt)
{
	if (m_accel > 0.0)
		m_vel += m_accel*dt;
	else
		m_vel -= m_velweight*m_vel*dt;

	if (m_vel > m_maxvel) m_vel = m_maxvel;
	if (m_vel < 0.00001) m_vel = 0.0;

	if (m_zoomaccel > 0.0)
		m_zoomvel += m_zoomaccel*dt;
	else
		m_zoomvel -= m_zoomvelweight*m_zoomvel*dt;

	if (m_zoomvel > m_maxzoomvel) m_zoomvel = m_maxzoomvel;
	if (m_zoomvel < 0.00001) m_zoomvel = 0.0;

	if (m_zoomvel)
		zoom(m_zoomin, m_zoomx, m_zoomy, m_zoomvel*dt);
	if (m_vel)
		m_pos += getAccelerationVector()*m_vel*dt;

	computeMatrices();
}

Vec3d
TopDownViewer::getAccelerationVector()
{
	Vec3d accelvec;

	if (m_accelkey == 'd')
		accelvec = -Vec3d(1.0, 0.0, 0.0);
	else if (m_accelkey == 'a')
		accelvec = Vec3d(1.0, 0.0, 0.0);
	else if (m_accelkey == 'e')
		accelvec = -Vec3d(0.0, 1.0, 0.0);
	else if (m_accelkey == 'c')
		accelvec = Vec3d(0.0, 1.0, 0.0);

	return accelvec;
}

void
TopDownViewer::keyboard(unsigned char c, int x, int y)
{
	++m_accelkeys;

	if (c == 'a' || c == 'd' || c == 'e' || c == 'c')
	{
		m_accelkey = c;
		m_zoomaccel = m_zoomvel = 0;
		m_accel = m_maxaccel;
	}
	else if (c == 's')
	{
		m_accel = m_vel = 0;
		m_zoomaccel = m_maxzoomaccel;
		m_zoomin = false;
	}
	else if (c == 'w')
	{
		m_accel = m_vel = 0;
		m_zoomaccel = m_maxzoomaccel;
		m_zoomin = true;
	}

	m_zoomx = x;
	m_zoomy = y;
}

void
TopDownViewer::keyboardUp(unsigned char c, int x, int y)
{
	if (--m_accelkeys <= 0)
	{
		m_accel = 0.0;
		m_zoomaccel = 0.0;
		m_accelkeys = 0;
	}
}

void
TopDownViewer::setMaxVelocity(double velocity)
{
	m_maxvel = velocity;
	m_maxzoomvel = velocity;
}

void
TopDownViewer::setMaxAcceleration(double acceleration)
{
	m_maxaccel = acceleration;
	m_maxzoomaccel = acceleration;
}

void
TopDownViewer::setVelocityAttenuation(double attenuation)
{
	m_velweight = attenuation;
	m_zoomvelweight = attenuation;
}

void
TopDownViewer::wheel(int x, int y, bool zoomin)
{
    zoom(zoomin, x, y, 0.05);
}

};
