#ifndef PROJECTION_H
#define PROJECTION_H

#include "Matrix.h"
#include "Vector.h"

#include "glcorearb.h"

namespace gbox
{

class Projection
{
public:
	// fit2DWindow() will resize the (existing) 2d float space window (what you'd pass as args to ortho2D)
	// by extending either the width or the height such that the new aspect ratio matches that of the viewport.
	// This is very handy to prevent image distortion when doing the window to viewport transformation.
	static void fit2DWindow (GLsizei vpw, GLsizei vph, GLdouble &l, GLdouble &r, GLdouble &b, GLdouble &t);

	static Mat4d ortho   (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);
	static Mat4d ortho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);

	static Mat4d frustum     (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);
	static Mat4d perspective (GLdouble vfov, GLdouble aspect, GLdouble near, GLdouble far);

	static void perspective2DWindow (GLdouble vfov, GLdouble aspect, GLdouble n,
	                                 GLdouble &l, GLdouble &r, GLdouble &b, GLdouble &t);

	static bool unproject (const Vec3d &winp, const Mat4d &modelmat, const Mat4d projmat, const Vec4i &viewport, Vec3d &objp);
};

};

#endif
