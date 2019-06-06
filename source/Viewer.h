#ifndef VIEWER_H
#define VIEWER_H

#include "Types.h"
#include "Vector.h"
#include "Matrix.h"
#include "GLBase.h"

namespace gbox
{

class Viewer : public GLBase
{
public:
	Mat4d getViewMatrix () const;
	Mat4d getProjMatrix () const;

	virtual void timestep (double dt) {}

	virtual void reset () {}

	virtual void keyboard   (unsigned char c, int x, int y) {}
	virtual void keyboardUp (unsigned char c, int x, int y) {}

	virtual void special (int c, int x, int y) {}
	virtual void motion  (PointerButton btn, ButtonState s, int prevx, int prevy, int x, int y) {}
	virtual void pointer (PointerButton pos, ButtonState s, int x, int y) {}

	virtual void windowResize (int width, int height) {}

	virtual void setMaxVelocity         (double velocity);
	virtual void setMaxAcceleration     (double acceleration);
	virtual void setVelocityAttenuation (double attenuation);

	virtual ~Viewer () {}

	void setViewport (GLint x, GLint y, GLsizei width, GLsizei height);

	void unproject (const Vec3d &winp, Vec3d &objp);

	static Mat4d lookAt (double eyex, double eyey, double eyez,
	                     double centerx, double centery, double centerz,
	                     double upx, double upy, double upz);

protected:
	Viewer ();

	Mat4d m_view, m_proj;

	Vec4i m_viewport;

	bool m_initial;

	int m_prevwinw, m_prevwinh;

	Vec2d m_boxmin, m_boxmax;

	double m_accel, m_vel;

	int m_accelkeys;

	unsigned char m_accelkey;

	double m_velweight;

	double m_maxaccel, m_maxvel;
};

class LandscapeViewer : public Viewer
{
public:
	LandscapeViewer ();

	void timestep (double dt);

	void reset () {}

	void setPosition    (const Vec3d &pos);
	void setOrientation (const Vec3d &hpr);

	Vec3d getPosition    () const;
	Vec3d getOrientation () const;

	void windowResize (int width, int height);

	Mat4d setPerspective (GLdouble vfov, GLdouble aspect, GLdouble near, GLdouble far);

	void keyboard   (unsigned char c, int x, int y);
	void keyboardUp (unsigned char c, int x, int y);

	void motion (PointerButton btn, ButtonState s, int prevx, int prevy, int x, int y);

protected:
	void updateDir       ();
	void computeMatrices ();
	void updateAll       ();

	Vec3d getAccelerationVector ();

	Vec3d m_pos, m_hpr, m_dir;

	double m_nearclip, m_farclip;
};

class TopDownViewer : public Viewer
{
public:
	TopDownViewer ();

	void reset ();

	void timestep (double dt);

	void  setPosition (const Vec3d &pos);
	Vec3d getPosition () const;

	void windowResize (int width, int height);

	void set2DWindow (double l, double r, double b, double t);

	void setZoomFactor (double zoomfac);

	void setMaxVelocity         (double velocity);
	void setMaxAcceleration     (double acceleration);
	void setVelocityAttenuation (double attenuation);

	void keyboard   (unsigned char c, int x, int y);
	void keyboardUp (unsigned char c, int x, int y);

	void motion   (PointerButton btn, ButtonState s, int prevx, int prevy, int x, int y);
	void pointer  (PointerButton pos, ButtonState s, int x, int y);

    void wheel (int x, int y, bool zoomin);

protected:
	void computeMatrices ();

	void zoom (bool in, int x, int y, double d = 0.1);

	Vec3d getAccelerationVector ();

	Vec3d m_pos;

	bool m_zoomin;

	int m_zoomx, m_zoomy;

	Vec3d m_pivot;

	double m_zoomaccel, m_zoomvel;

	double m_zoomvelweight;

	double m_maxzoomaccel, m_maxzoomvel;

	double m_zoomfac;
};

};

#endif
