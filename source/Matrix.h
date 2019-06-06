#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

namespace gbox
{

template <typename T>
struct Mat2
{
	T n[2][2];

	Mat2 ()
	{
		setIdentity();
	}

	Mat2 (T n00, T n01,
	      T n10, T n11)
	{
		n[0][0] = n00;
		n[0][1] = n10;

		n[1][0] = n01;
		n[1][1] = n11;
	}

	Mat2 &set (T n00, T n01,
	           T n10, T n11)
	{
		n[0][0] = n00;
		n[0][1] = n10;

		n[1][0] = n01;
		n[1][1] = n11;
		return (*this);
	}

	T &operator () (unsigned int row, unsigned int col)
	{
		return (n[col][row]);
	}

	const T &operator ()(unsigned int row, unsigned int col) const
	{
		return (n[col][row]);
	}

	Vec2<T> row (unsigned int i) const
	{
		return Vec2<T>(n[0][i], n[1][i]);
	}

	Mat2 &setRow (unsigned int i, const Vec2<T> &row)
	{
		n[0][i] = row.x();
		n[1][i] = row.y();
		return (*this);
	}

	Vec2<T> col (unsigned int i) const
	{
		return Vec2<T>(n[i][0], n[i][1]);
	}

	Mat2 &setCol (unsigned int i, const Vec2<T> &col)
	{
		n[i][0] = col.x();
		n[i][1] = col.y();
		return (*this);
	}

	Mat2 &setIdentity (void)
	{
		n[0][0] = n[1][1] = 1;
		n[1][0] = n[0][1] = 0;
		return (*this);
	}

	Mat2 &operator *= (const Mat2 &m)
	{
		T t = n[0][0] * m.n[0][0] + n[1][0] * m.n[0][1];
		T u = n[0][0] * m.n[1][0] + n[1][0] * m.n[1][1];
		n[0][0] = t;
		n[1][0] = u;

		t = n[0][1] * m.n[0][0] + n[1][1] * m.n[0][1];
		u = n[0][1] * m.n[1][0] + n[1][1] * m.n[1][1];
		n[0][1] = t;
		n[1][1] = u;

		return (*this);
	}

	T * ptr()
	{
		return (T *) n;
	}

	const T * ptr() const
	{
		return (const T *) n;
	}
};

template <typename T>
Mat2<T> operator * (const Mat2<T> &m1, const Mat2<T> &m2)
{
	return (Mat2<T>(m1.n[0][0] * m2.n[0][0] + m1.n[1][0] * m2.n[0][1],
	                m1.n[0][0] * m2.n[1][0] + m1.n[1][0] * m2.n[1][1],
	                m1.n[0][1] * m2.n[0][0] + m1.n[1][1] * m2.n[0][1],
	                m1.n[0][1] * m2.n[1][0] + m1.n[1][1] * m2.n[1][1]));
}

template <typename T>
Vec2<T> operator * (const Vec2<T> &v, const Mat2<T> &m)
{
	return (Vec2<T>(m.n[0][0] * v.x() + m.n[0][1] * v.y(),
	                m.n[1][0] * v.x() + m.n[1][1] * v.y()));
}

template <typename T>
Vec2<T> operator * (const Mat2<T> &m, const Vec2<T> &v)
{
	return (Vec2<T>(m.n[0][0] * v.x() + m.n[1][0] * v.y(),
	                m.n[0][1] * v.x() + m.n[1][1] * v.y()));
}

template <typename T>
bool operator == (const Mat2<T> &m1, const Mat2<T> &m2)
{
	return ((m1.n[0][0] == m2.n[0][0]) && (m1.n[0][1] == m2.n[0][1]) &&
	        (m1.n[1][0] == m2.n[1][0]) && (m1.n[1][1] == m2.n[1][1]));
}

template <typename T>
bool operator != (const Mat2<T> &m1, const Mat2<T> &m2)
{
	return ((m1.n[0][0] != m2.n[0][0]) || (m1.n[0][1] != m2.n[0][1]) ||
	        (m1.n[1][0] != m2.n[1][0]) || (m1.n[1][1] != m2.n[1][1]));
}

template <typename T>
T determinant(const Mat2<T> &m)
{
	return (m.n[0][0] * m.n[1][1] - m.n[0][1] * m.n[1][0]);
}

template <typename T>
Mat2<T> transpose (const Mat2<T> &m)
{
	return (Mat2<T>(m.n[0][0], m.n[0][1],
	                m.n[1][0], m.n[1][1]));
}

template <typename T>
Mat2<T> inverse (const Mat2<T> &m)
{
	T t = 1.0f / (m.n[0][0] * m.n[1][1] - m.n[0][1] * m.n[1][0]);

	return (Mat2<T>( m.n[1][1]*t, -m.n[1][0]*t,
	                -m.n[0][1]*t,  m.n[0][0]*t));
}

template <typename T>
struct Mat3
{
	T n[3][3];

	Mat3 ()
	{
		setIdentity();
	}

	Mat3 (T n00, T n01, T n02,
	      T n10, T n11, T n12,
	      T n20, T n21, T n22)
	{
		n[0][0] = n00;
		n[0][1] = n10;
		n[0][2] = n20;

		n[1][0] = n01;
		n[1][1] = n11;
		n[1][2] = n21;

		n[2][0] = n02;
		n[2][1] = n12;
		n[2][2] = n22;
	}

	Mat3 &set (T n00, T n01, T n02,
	           T n10, T n11, T n12,
	           T n20, T n21, T n22)
	{
		n[0][0] = n00;
		n[0][1] = n10;
		n[0][2] = n20;

		n[1][0] = n01;
		n[1][1] = n11;
		n[1][2] = n21;

		n[2][0] = n02;
		n[2][1] = n12;
		n[2][2] = n22;
		return (*this);
	}

	T &operator () (unsigned int row, unsigned int col)
	{
		return (n[col][row]);
	}

	const T &operator ()(unsigned int row, unsigned int col) const
	{
		return (n[col][row]);
	}

	Vec3<T> row (unsigned int i) const
	{
		return Vec3<T>(n[0][i], n[1][i], n[2][i]);
	}

	Mat3 &setRow (unsigned int i, const Vec3<T> &row)
	{
		n[0][i] = row.x();
		n[1][i] = row.y();
		n[2][i] = row.z();
		return (*this);
	}

	Vec3<T> col (unsigned int i) const
	{
		return Vec3<T>(n[i][0], n[i][1], n[i][2]);
	}

	Mat3 &setCol (unsigned int i, const Vec3<T> &col)
	{
		n[i][0] = col.x();
		n[i][1] = col.y();
		n[i][2] = col.z();
		return (*this);
	}

	Mat3 &setIdentity (void)
	{
		n[0][0] = n[1][1] = n[2][2] = 1;
		n[1][0] = n[2][0] = n[0][1] = n[2][1] = n[0][2] = n[1][2] = 0;
		return (*this);
	}

	Mat3 &operator *= (const Mat3 &m)
	{
		T t = n[0][0] * m.n[0][0] + n[1][0] * m.n[0][1] + n[2][0] * m.n[0][2];
		T u = n[0][0] * m.n[1][0] + n[1][0] * m.n[1][1] + n[2][0] * m.n[1][2];
		n[2][0] = n[0][0] * m.n[2][0] + n[1][0] * m.n[2][1] + n[2][0] * m.n[2][2];
		n[0][0] = t;
		n[1][0] = u;

		t = n[0][1] * m.n[0][0] + n[1][1] * m.n[0][1] + n[2][1] * m.n[0][2];
		u = n[0][1] * m.n[1][0] + n[1][1] * m.n[1][1] + n[2][1] * m.n[1][2];
		n[2][1] = n[0][1] * m.n[2][0] + n[1][1] * m.n[2][1] + n[2][1] * m.n[2][2];
		n[0][1] = t;
		n[1][1] = u;

		t = n[0][2] * m.n[0][0] + n[1][2] * m.n[0][1] + n[2][2] * m.n[0][2];
		u = n[0][2] * m.n[1][0] + n[1][2] * m.n[1][1] + n[2][2] * m.n[1][2];
		n[2][2] = n[0][2] * m.n[2][0] + n[1][2] * m.n[2][1] + n[2][2] * m.n[2][2];
		n[0][2] = t;
		n[1][2] = u;

		return (*this);
	}

	T * ptr()
	{
		return (T *) n;
	}

	const T * ptr() const
	{
		return (const T *) n;
	}
};

template <typename T>
Mat3<T> operator * (const Mat3<T> &m1, const Mat3<T> &m2)
{
	return (Mat3<T>(m1.n[0][0] * m2.n[0][0] + m1.n[1][0] * m2.n[0][1] + m1.n[2][0] * m2.n[0][2],
	                m1.n[0][0] * m2.n[1][0] + m1.n[1][0] * m2.n[1][1] + m1.n[2][0] * m2.n[1][2],
	                m1.n[0][0] * m2.n[2][0] + m1.n[1][0] * m2.n[2][1] + m1.n[2][0] * m2.n[2][2],
	                m1.n[0][1] * m2.n[0][0] + m1.n[1][1] * m2.n[0][1] + m1.n[2][1] * m2.n[0][2],
	                m1.n[0][1] * m2.n[1][0] + m1.n[1][1] * m2.n[1][1] + m1.n[2][1] * m2.n[1][2],
	                m1.n[0][1] * m2.n[2][0] + m1.n[1][1] * m2.n[2][1] + m1.n[2][1] * m2.n[2][2],
	                m1.n[0][2] * m2.n[0][0] + m1.n[1][2] * m2.n[0][1] + m1.n[2][2] * m2.n[0][2],
	                m1.n[0][2] * m2.n[1][0] + m1.n[1][2] * m2.n[1][1] + m1.n[2][2] * m2.n[1][2],
	                m1.n[0][2] * m2.n[2][0] + m1.n[1][2] * m2.n[2][1] + m1.n[2][2] * m2.n[2][2]));
}

template <typename T>
Vec3<T> operator * (const Vec3<T> &v, const Mat3<T> &m)
{
	return (Vec3<T>(m.n[0][0] * v.x() + m.n[0][1] * v.y() + m.n[0][2] * v.z(),
	                m.n[1][0] * v.x() + m.n[1][1] * v.y() + m.n[1][2] * v.z(),
	                m.n[2][0] * v.x() + m.n[2][1] * v.y() + m.n[2][2] * v.z()));
}

template <typename T>
Vec3<T> operator * (const Mat3<T> &m, const Vec3<T> &v)
{
	return (Vec3<T>(m.n[0][0] * v.x() + m.n[1][0] * v.y() + m.n[2][0] * v.z(),
	                m.n[0][1] * v.x() + m.n[1][1] * v.y() + m.n[2][1] * v.z(),
	                m.n[0][2] * v.x() + m.n[1][2] * v.y() + m.n[2][2] * v.z()));
}

template <typename T>
bool operator == (const Mat3<T> &m1, const Mat3<T> &m2)
{
	return ((m1.n[0][0] == m2.n[0][0]) && (m1.n[0][1] == m2.n[0][1]) && (m1.n[0][2] == m2.n[0][2]) &&
	        (m1.n[1][0] == m2.n[1][0]) && (m1.n[1][1] == m2.n[1][1]) && (m1.n[1][2] == m2.n[1][2]) &&
	        (m1.n[2][0] == m2.n[2][0]) && (m1.n[2][1] == m2.n[2][1]) && (m1.n[2][2] == m2.n[2][2]));
}

template <typename T>
bool operator != (const Mat3<T> &m1, const Mat3<T> &m2)
{
	return ((m1.n[0][0] != m2.n[0][0]) || (m1.n[0][1] != m2.n[0][1]) || (m1.n[0][2] != m2.n[0][2]) ||
	        (m1.n[1][0] != m2.n[1][0]) || (m1.n[1][1] != m2.n[1][1]) || (m1.n[1][2] != m2.n[1][2]) ||
	        (m1.n[2][0] != m2.n[2][0]) || (m1.n[2][1] != m2.n[2][1]) || (m1.n[2][2] != m2.n[2][2]));
}

template <typename T>
T determinant(const Mat3<T> &m)
{
	return (m.n[0][0] * (m.n[1][1] * m.n[2][2] - m.n[1][2] * m.n[2][1]) - m.n[0][1] * (m.n[1][0] * m.n[2][2] -
	        m.n[1][2] * m.n[2][0]) + m.n[0][2] * (m.n[1][0] * m.n[2][1] - m.n[1][1] * m.n[2][0]));
}

template <typename T>
Mat3<T> transpose (const Mat3<T> &m)
{
	return (Mat3<T>(m.n[0][0], m.n[0][1], m.n[0][2],
	                m.n[1][0], m.n[1][1], m.n[1][2],
	                m.n[2][0], m.n[2][1], m.n[2][2]));
}

template <typename T>
Mat3<T> inverse (const Mat3<T> &m)
{
	T n00 = m.n[0][0];
	T n01 = m.n[1][0];
	T n02 = m.n[2][0];
	T n10 = m.n[0][1];
	T n11 = m.n[1][1];
	T n12 = m.n[2][1];
	T n20 = m.n[0][2];
	T n21 = m.n[1][2];
	T n22 = m.n[2][2];

	T p00 = n11 * n22 - n12 * n21;
	T p10 = n12 * n20 - n10 * n22;
	T p20 = n10 * n21 - n11 * n20;

	T t = 1.0f / (n00 * p00 + n01 * p10 + n02 * p20);

	return (Mat3<T>(p00 * t, (n02 * n21 - n01 * n22) * t, (n01 * n12 - n02 * n11) * t,
	                p10 * t, (n00 * n22 - n02 * n20) * t, (n02 * n10 - n00 * n12) * t,
	                p20 * t, (n01 * n20 - n00 * n21) * t, (n00 * n11 - n01 * n10) * t));
}

template <typename T>
struct Mat4
{
	T n[4][4];

	Mat4 ()
	{
		setIdentity();
	}

	Mat4 (T n00, T n01, T n02, T n03,
	      T n10, T n11, T n12, T n13,
	      T n20, T n21, T n22, T n23,
	      T n30, T n31, T n32, T n33)
	{
		n[0][0] = n00;
		n[0][1] = n10;
		n[0][2] = n20;
		n[0][3] = n30;

		n[1][0] = n01;
		n[1][1] = n11;
		n[1][2] = n21;
		n[1][3] = n31;

		n[2][0] = n02;
		n[2][1] = n12;
		n[2][2] = n22;
		n[2][3] = n32;

		n[3][0] = n03;
		n[3][1] = n13;
		n[3][2] = n23;
		n[3][3] = n33;
	}

	Mat4 &set (T n00, T n01, T n02, T n03,
	           T n10, T n11, T n12, T n13,
	           T n20, T n21, T n22, T n23,
	           T n30, T n31, T n32, T n33)
	{
		n[0][0] = n00;
		n[0][1] = n10;
		n[0][2] = n20;
		n[0][3] = n30;

		n[1][0] = n01;
		n[1][1] = n11;
		n[1][2] = n21;
		n[1][3] = n31;

		n[2][0] = n02;
		n[2][1] = n12;
		n[2][2] = n22;
		n[2][3] = n32;

		n[3][0] = n03;
		n[3][1] = n13;
		n[3][2] = n23;
		n[3][3] = n33;
		return (*this);
	}

	T &operator () (unsigned int row, unsigned int col)
	{
		return (n[col][row]);
	}

	const T &operator ()(unsigned int row, unsigned int col) const
	{
		return (n[col][row]);
	}

	Vec4<T> row (unsigned int i) const
	{
		return Vec4<T>(n[0][i], n[1][i], n[2][i], n[3][i]);
	}

	Mat4 &setRow (unsigned int i, const Vec4<T> &row)
	{
		n[0][i] = row.x();
		n[1][i] = row.y();
		n[2][i] = row.z();
		n[3][i] = row.w();
		return (*this);
	}

	Vec4<T> col (unsigned int i) const
	{
		return Vec4<T>(n[i][0], n[i][1], n[i][2], n[i][3]);
	}

	Mat4 &setCol (unsigned int i, const Vec4<T> &col)
	{
		n[i][0] = col.x();
		n[i][1] = col.y();
		n[i][2] = col.z();
		n[i][3] = col.w();
		return (*this);
	}

	Mat4 &setIdentity (void)
	{
		n[0][0] = n[1][1] = n[2][2] = n[3][3] = 1;
		n[1][0] = n[2][0] = n[3][0] = n[0][1] = n[2][1] = n[3][1] = n[0][2] = n[1][2] = n[3][2] = n[0][3] = n[1][3] = n[2][3] = 0;
		return (*this);
	}

	Mat4 &operator *= (const Mat4 &m)
	{
		T x = n[0][0];
		T y = n[1][0];
		T z = n[2][0];
		T w = n[3][0];
		n[0][0] = x * m.n[0][0] + y * m.n[0][1] + z * m.n[0][2] + w * m.n[0][3];
		n[1][0] = x * m.n[1][0] + y * m.n[1][1] + z * m.n[1][2] + w * m.n[1][3];
		n[2][0] = x * m.n[2][0] + y * m.n[2][1] + z * m.n[2][2] + w * m.n[2][3];
		n[3][0] = x * m.n[3][0] + y * m.n[3][1] + z * m.n[3][2] + w * m.n[3][3];

		x = n[0][1];
		y = n[1][1];
		z = n[2][1];
		w = n[3][1];
		n[0][1] = x * m.n[0][0] + y * m.n[0][1] + z * m.n[0][2] + w * m.n[0][3];
		n[1][1] = x * m.n[1][0] + y * m.n[1][1] + z * m.n[1][2] + w * m.n[1][3];
		n[2][1] = x * m.n[2][0] + y * m.n[2][1] + z * m.n[2][2] + w * m.n[2][3];
		n[3][1] = x * m.n[3][0] + y * m.n[3][1] + z * m.n[3][2] + w * m.n[3][3];

		x = n[0][2];
		y = n[1][2];
		z = n[2][2];
		w = n[3][2];
		n[0][2] = x * m.n[0][0] + y * m.n[0][1] + z * m.n[0][2] + w * m.n[0][3];
		n[1][2] = x * m.n[1][0] + y * m.n[1][1] + z * m.n[1][2] + w * m.n[1][3];
		n[2][2] = x * m.n[2][0] + y * m.n[2][1] + z * m.n[2][2] + w * m.n[2][3];
		n[3][2] = x * m.n[3][0] + y * m.n[3][1] + z * m.n[3][2] + w * m.n[3][3];

		x = n[0][3];
		y = n[1][3];
		z = n[2][3];
		w = n[3][3];
		n[0][3] = x * m.n[0][0] + y * m.n[0][1] + z * m.n[0][2] + w * m.n[0][3];
		n[1][3] = x * m.n[1][0] + y * m.n[1][1] + z * m.n[1][2] + w * m.n[1][3];
		n[2][3] = x * m.n[2][0] + y * m.n[2][1] + z * m.n[2][2] + w * m.n[2][3];
		n[3][3] = x * m.n[3][0] + y * m.n[3][1] + z * m.n[3][2] + w * m.n[3][3];

		return (*this);
	}

	T * ptr()
	{
		return (T *) n;
	}

	const T * ptr() const
	{
		return (const T *) n;
	}
};

template <typename T>
Mat4<T> operator * (const Mat4<T> &m1, const Mat4<T> &m2)
{
	return (Mat4<T>(m1.n[0][0] * m2.n[0][0] + m1.n[1][0] * m2.n[0][1] + m1.n[2][0] * m2.n[0][2] + m1.n[3][0] * m2.n[0][3],
	                m1.n[0][0] * m2.n[1][0] + m1.n[1][0] * m2.n[1][1] + m1.n[2][0] * m2.n[1][2] + m1.n[3][0] * m2.n[1][3],
	                m1.n[0][0] * m2.n[2][0] + m1.n[1][0] * m2.n[2][1] + m1.n[2][0] * m2.n[2][2] + m1.n[3][0] * m2.n[2][3],
	                m1.n[0][0] * m2.n[3][0] + m1.n[1][0] * m2.n[3][1] + m1.n[2][0] * m2.n[3][2] + m1.n[3][0] * m2.n[3][3],
	                m1.n[0][1] * m2.n[0][0] + m1.n[1][1] * m2.n[0][1] + m1.n[2][1] * m2.n[0][2] + m1.n[3][1] * m2.n[0][3],
	                m1.n[0][1] * m2.n[1][0] + m1.n[1][1] * m2.n[1][1] + m1.n[2][1] * m2.n[1][2] + m1.n[3][1] * m2.n[1][3],
	                m1.n[0][1] * m2.n[2][0] + m1.n[1][1] * m2.n[2][1] + m1.n[2][1] * m2.n[2][2] + m1.n[3][1] * m2.n[2][3],
	                m1.n[0][1] * m2.n[3][0] + m1.n[1][1] * m2.n[3][1] + m1.n[2][1] * m2.n[3][2] + m1.n[3][1] * m2.n[3][3],
	                m1.n[0][2] * m2.n[0][0] + m1.n[1][2] * m2.n[0][1] + m1.n[2][2] * m2.n[0][2] + m1.n[3][2] * m2.n[0][3],
	                m1.n[0][2] * m2.n[1][0] + m1.n[1][2] * m2.n[1][1] + m1.n[2][2] * m2.n[1][2] + m1.n[3][2] * m2.n[1][3],
	                m1.n[0][2] * m2.n[2][0] + m1.n[1][2] * m2.n[2][1] + m1.n[2][2] * m2.n[2][2] + m1.n[3][2] * m2.n[2][3],
	                m1.n[0][2] * m2.n[3][0] + m1.n[1][2] * m2.n[3][1] + m1.n[2][2] * m2.n[3][2] + m1.n[3][2] * m2.n[3][3],
	                m1.n[0][3] * m2.n[0][0] + m1.n[1][3] * m2.n[0][1] + m1.n[2][3] * m2.n[0][2] + m1.n[3][3] * m2.n[0][3],
	                m1.n[0][3] * m2.n[1][0] + m1.n[1][3] * m2.n[1][1] + m1.n[2][3] * m2.n[1][2] + m1.n[3][3] * m2.n[1][3],
	                m1.n[0][3] * m2.n[2][0] + m1.n[1][3] * m2.n[2][1] + m1.n[2][3] * m2.n[2][2] + m1.n[3][3] * m2.n[2][3],
	                m1.n[0][3] * m2.n[3][0] + m1.n[1][3] * m2.n[3][1] + m1.n[2][3] * m2.n[3][2] + m1.n[3][3] * m2.n[3][3]));
}

template <typename T>
Vec4<T> operator * (const Vec4<T> &v, const Mat4<T> &m)
{
	return (Vec4<T>(m.n[0][0] * v.x() + m.n[0][1] * v.y() + m.n[0][2] * v.z() + m.n[0][3] * v.w(),
	                m.n[1][0] * v.x() + m.n[1][1] * v.y() + m.n[1][2] * v.z() + m.n[1][3] * v.w(),
	                m.n[2][0] * v.x() + m.n[2][1] * v.y() + m.n[2][2] * v.z() + m.n[2][3] * v.w(),
	                m.n[3][0] * v.x() + m.n[3][1] * v.y() + m.n[3][2] * v.z() + m.n[3][3] * v.w()));
}

template <typename T>
Vec4<T> operator * (const Mat4<T> &m, const Vec4<T> &v)
{
	return (Vec4<T>(m.n[0][0] * v.x() + m.n[1][0] * v.y() + m.n[2][0] * v.z() + m.n[3][0] * v.w(),
	                m.n[0][1] * v.x() + m.n[1][1] * v.y() + m.n[2][1] * v.z() + m.n[3][1] * v.w(),
	                m.n[0][2] * v.x() + m.n[1][2] * v.y() + m.n[2][2] * v.z() + m.n[3][2] * v.w(),
	                m.n[0][3] * v.x() + m.n[1][3] * v.y() + m.n[2][3] * v.z() + m.n[3][3] * v.w()));
}

template <typename T>
bool operator == (const Mat4<T> &m1, const Mat4<T> &m2)
{
	return ((m1.n[0][0] == m2.n[0][0]) && (m1.n[0][1] == m2.n[0][1]) && (m1.n[0][2] == m2.n[0][2]) && (m1.n[0][3] == m2.n[0][3]) &&
	        (m1.n[1][0] == m2.n[1][0]) && (m1.n[1][1] == m2.n[1][1]) && (m1.n[1][2] == m2.n[1][2]) && (m1.n[1][3] == m2.n[1][3]) &&
	        (m1.n[2][0] == m2.n[2][0]) && (m1.n[2][1] == m2.n[2][1]) && (m1.n[2][2] == m2.n[2][2]) && (m1.n[2][3] == m2.n[2][3]) &&
	        (m1.n[3][0] == m2.n[3][0]) && (m1.n[3][1] == m2.n[3][1]) && (m1.n[3][2] == m2.n[3][2]) && (m1.n[3][3] == m2.n[3][3]));
}

template <typename T>
bool operator != (const Mat4<T> &m1, const Mat4<T> &m2)
{
	return ((m1.n[0][0] != m2.n[0][0]) || (m1.n[0][1] != m2.n[0][1]) || (m1.n[0][2] != m2.n[0][2]) || (m1.n[0][3] != m2.n[0][3]) ||
	        (m1.n[1][0] != m2.n[1][0]) || (m1.n[1][1] != m2.n[1][1]) || (m1.n[1][2] != m2.n[1][2]) || (m1.n[1][3] != m2.n[1][3]) ||
	        (m1.n[2][0] != m2.n[2][0]) || (m1.n[2][1] != m2.n[2][1]) || (m1.n[2][2] != m2.n[2][2]) || (m1.n[2][3] != m2.n[2][3]) ||
	        (m1.n[3][0] != m2.n[3][0]) || (m1.n[3][1] != m2.n[3][1]) || (m1.n[3][2] != m2.n[3][2]) || (m1.n[3][3] != m2.n[3][3]));
}

template <typename T>
T determinant(const Mat4<T> &m)
{
	T n00 = m.n[0][0];
	T n01 = m.n[1][0];
	T n02 = m.n[2][0];
	T n03 = m.n[3][0];

	T n10 = m.n[0][1];
	T n11 = m.n[1][1];
	T n12 = m.n[2][1];
	T n13 = m.n[3][1];

	T n20 = m.n[0][2];
	T n21 = m.n[1][2];
	T n22 = m.n[2][2];
	T n23 = m.n[3][2];

	T n30 = m.n[0][3];
	T n31 = m.n[1][3];
	T n32 = m.n[2][3];
	T n33 = m.n[3][3];

	return (n00 * (n11 * (n22 * n33 - n23 * n32) + n12 * (n23 * n31 - n21 * n33) + n13 * (n21 * n32 - n22 * n31)) +
	        n01 * (n10 * (n23 * n32 - n22 * n33) + n12 * (n20 * n33 - n23 * n30) + n13 * (n22 * n30 - n20 * n32)) +
	        n02 * (n10 * (n21 * n33 - n23 * n31) + n11 * (n23 * n30 - n20 * n33) + n13 * (n20 * n31 - n21 * n30)) +
	        n03 * (n10 * (n22 * n31 - n21 * n32) + n11 * (n20 * n32 - n22 * n30) + n12 * (n21 * n30 - n20 * n31)));
}

template <typename T>
Mat4<T> transpose (const Mat4<T> &m)
{
	return (Mat4<T>(m.n[0][0], m.n[0][1], m.n[0][2], m.n[0][3],
	                m.n[1][0], m.n[1][1], m.n[1][2], m.n[1][3],
	                m.n[2][0], m.n[2][1], m.n[2][2], m.n[2][3],
	                m.n[3][0], m.n[3][1], m.n[3][2], m.n[3][3]));
}

template <typename T>
Mat4<T> inverse (const Mat4<T> &m)
{
	T n00 = m.n[0][0];
	T n01 = m.n[1][0];
	T n02 = m.n[2][0];
	T n03 = m.n[3][0];

	T n10 = m.n[0][1];
	T n11 = m.n[1][1];
	T n12 = m.n[2][1];
	T n13 = m.n[3][1];

	T n20 = m.n[0][2];
	T n21 = m.n[1][2];
	T n22 = m.n[2][2];
	T n23 = m.n[3][2];

	T n30 = m.n[0][3];
	T n31 = m.n[1][3];
	T n32 = m.n[2][3];
	T n33 = m.n[3][3];

	T p00 = n11 * (n22 * n33 - n23 * n32) + n12 * (n23 * n31 - n21 * n33) + n13 * (n21 * n32 - n22 * n31);
	T p10 = n10 * (n23 * n32 - n22 * n33) + n12 * (n20 * n33 - n23 * n30) + n13 * (n22 * n30 - n20 * n32);
	T p20 = n10 * (n21 * n33 - n23 * n31) + n11 * (n23 * n30 - n20 * n33) + n13 * (n20 * n31 - n21 * n30);
	T p30 = n10 * (n22 * n31 - n21 * n32) + n11 * (n20 * n32 - n22 * n30) + n12 * (n21 * n30 - n20 * n31);

	T t = 1.0f / (n00 * p00 + n01 * p10 + n02 * p20 + n03 * p30);

	return (Mat4<T>(p00 * t,
	                (n01 * (n23 * n32 - n22 * n33) + n02 * (n21 * n33 - n23 * n31) + n03 * (n22 * n31 - n21 * n32)) * t,
	                (n01 * (n12 * n33 - n13 * n32) + n02 * (n13 * n31 - n11 * n33) + n03 * (n11 * n32 - n12 * n31)) * t,
	                (n01 * (n13 * n22 - n12 * n23) + n02 * (n11 * n23 - n13 * n21) + n03 * (n12 * n21 - n11 * n22)) * t,
	                p10 * t,
	                (n00 * (n22 * n33 - n23 * n32) + n02 * (n23 * n30 - n20 * n33) + n03 * (n20 * n32 - n22 * n30)) * t,
	                (n00 * (n13 * n32 - n12 * n33) + n02 * (n10 * n33 - n13 * n30) + n03 * (n12 * n30 - n10 * n32)) * t,
	                (n00 * (n12 * n23 - n13 * n22) + n02 * (n13 * n20 - n10 * n23) + n03 * (n10 * n22 - n12 * n20)) * t,
	                p20 * t,
	                (n00 * (n23 * n31 - n21 * n33) + n01 * (n20 * n33 - n23 * n30) + n03 * (n21 * n30 - n20 * n31)) * t,
	                (n00 * (n11 * n33 - n13 * n31) + n01 * (n13 * n30 - n10 * n33) + n03 * (n10 * n31 - n11 * n30)) * t,
	                (n00 * (n13 * n21 - n11 * n23) + n01 * (n10 * n23 - n13 * n20) + n03 * (n11 * n20 - n10 * n21)) * t,
	                p30 * t,
	                (n00 * (n21 * n32 - n22 * n31) + n01 * (n22 * n30 - n20 * n32) + n02 * (n20 * n31 - n21 * n30)) * t,
	                (n00 * (n12 * n31 - n11 * n32) + n01 * (n10 * n32 - n12 * n30) + n02 * (n11 * n30 - n10 * n31)) * t,
	                (n00 * (n11 * n22 - n12 * n21) + n01 * (n12 * n20 - n10 * n22) + n02 * (n10 * n21 - n11 * n20)) * t));
}

typedef Mat2<float> Mat2f;
typedef Mat2<double> Mat2d;

typedef Mat3<float> Mat3f;
typedef Mat3<double> Mat3d;

typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

};

#endif
