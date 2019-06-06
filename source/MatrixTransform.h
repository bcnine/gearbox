#ifndef MATRIX_TRANSFORM_H
#define MATRIX_TRANSFORM_H

#include "Vector.h"
#include "Matrix.h"

namespace gbox
{

inline Mat2d rotateZ2 (double radians)
{
	double cs = cos(radians);
	double sn = sin(radians);
	return Mat2d(cs, -sn,
	             sn,  cs);
}

};

#endif
