#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

// All vector structures (2, 3, 4) have the same interface, except that only Vec3 has cross product operators (%, %=).

namespace gbox
{

template<typename T>
class Vec2
{
public:
	Vec2()
	{
		m_v[0] = m_v[1] = 0;
	}

	Vec2 (T x, T y)
	{
		m_v[0] = x;
		m_v[1] = y;
	}

	Vec2 &set (T x, T y)
	{
		m_v[0] = x;
		m_v[1] = y;
		return (*this);
	}

	T &operator [] (unsigned int i)
	{
		return m_v[i];
	}

	const T &operator [] (unsigned int i) const
	{
		return m_v[i];
	}

	T & x ()
	{
		return m_v[0];
	}

	const T & x () const
	{
		return m_v[0];
	}

	T & y ()
	{
		return m_v[1];
	}

	const T & y () const
	{
		return m_v[1];
	}

	Vec2 &operator += (const Vec2 &v)
	{
		m_v[0] += v[0];
		m_v[1] += v[1];
		return (*this);
	}

	Vec2 &operator -= (const Vec2 &v)
	{
		m_v[0] -= v[0];
		m_v[1] -= v[1];
		return (*this);
	}
		
	Vec2 &operator *= (T t)
	{
		m_v[0] *= t;
		m_v[1] *= t;
		return (*this);
	}
		
	Vec2 &operator /= (T t)
	{
		T f = 1.0f / t;
		m_v[0] *= f;
		m_v[1] *= f;
		return (*this);
	}

	Vec2 &normalize ()
	{
		T f = 1.0f / mag(*this);
		m_v[0] *= f;
		m_v[1] *= f;
		return (*this);
	}

	T * ptr()
	{
		return m_v;
	}

	const T * ptr() const
	{
		return m_v;
	}

private:
	T m_v[2];
};

template <typename T> Vec2<T> operator- (const Vec2<T> &v)                     { return Vec2<T>(-v.x(), -v.y()); }
template <typename T> Vec2<T> operator* (T t, const Vec2<T> &v)                { return Vec2<T>(v.x()*t, v.y()*t); }
template <typename T> Vec2<T> operator* (const Vec2<T> &v, T t)                { return Vec2<T>(v.x()*t, v.y()*t); }
template <typename T> Vec2<T> operator/ (const Vec2<T> &v, T t)                { return Vec2<T>(v.x()/t, v.y()/t); }
template <typename T> Vec2<T> operator+ (const Vec2<T> &v1, const Vec2<T> &v2) { return Vec2<T>(v1.x()+v2.x(), v1.y()+v2.y()); }
template <typename T> Vec2<T> operator- (const Vec2<T> &v1, const Vec2<T> &v2) { return Vec2<T>(v1.x()-v2.x(), v1.y()-v2.y()); }

template <typename T> T operator* (const Vec2<T> &v1, const Vec2<T> &v2) { return (v1.x()*v2.x() + v1.y()*v2.y()); }

template <typename T> bool operator== (const Vec2<T> &v1, const Vec2<T> &v2) { return ((v1.x() == v2.x()) && (v1.y() == v2.y())); }
template <typename T> bool operator!= (const Vec2<T> &v1, const Vec2<T> &v2) { return ((v1.x() != v2.x()) || (v1.y() != v2.y())); }

template <typename T> Vec2<T> unit (const Vec2<T> &v) { return Vec2<T>(v).normalize(); }

inline float            mag   (const Vec2<float> &v) { return sqrtf(v.x()*v.x() + v.y()*v.y()); }
template <typename T> T mag   (const Vec2<T> &v)     { return sqrt(v.x()*v.x() + v.y()*v.y()); }
template <typename T> T sqmag (const Vec2<T> &v)     { return (v.x()*v.x() + v.y()*v.y()); }

template<typename T>
class Vec3
{
public:
	Vec3()
	{
		m_v[0] = m_v[1] = m_v[2] = 0;
	}

	Vec3 (T x, T y, T z)
	{
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z;
	}

	Vec3 &set (T x, T y, T z)
	{
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z;
		return (*this);
	}

	T &operator [] (unsigned int i)
	{
		return m_v[i];
	}

	const T &operator [] (unsigned int i) const
	{
		return m_v[i];
	}

	T & x ()
	{
		return m_v[0];
	}

	const T & x () const
	{
		return m_v[0];
	}

	T & y ()
	{
		return m_v[1];
	}

	const T & y () const
	{
		return m_v[1];
	}

	T & z ()
	{
		return m_v[2];
	}

	const T & z () const
	{
		return m_v[2];
	}

	Vec3 &operator += (const Vec3 &v)
	{
		m_v[0] += v[0];
		m_v[1] += v[1];
		m_v[2] += v[2];
		return (*this);
	}

	Vec3 &operator -= (const Vec3 &v)
	{
		m_v[0] -= v[0];
		m_v[1] -= v[1];
		m_v[2] -= v[2];
		return (*this);
	}
		
	Vec3 &operator *= (T t)
	{
		m_v[0] *= t;
		m_v[1] *= t;
		m_v[2] *= t;
		return (*this);
	}
		
	Vec3 &operator /= (T t)
	{
		T f = 1.0f / t;
		m_v[0] *= f;
		m_v[1] *= f;
		m_v[2] *= f;
		return (*this);
	}

	Vec3 &operator %= (const Vec3 &v)
	{
		T r, s;

		r = m_v[1] * v[2] - m_v[2] * v[1];
		s = m_v[2] * v[0] - m_v[0] * v[2];
		m_v[2] = m_v[0] * v[1] - m_v[1] * v[0];
		m_v[0] = r;
		m_v[1] = s;
		return (*this);
	}

	Vec3 &normalize ()
	{
		T f = 1.0f / mag(*this);
		m_v[0] *= f;
		m_v[1] *= f;
		m_v[2] *= f;
		return (*this);
	}

	T * ptr()
	{
		return m_v;
	}

	const T * ptr() const
	{
		return m_v;
	}

private:
	T m_v[3];
};

template <typename T> Vec3<T> operator- (const Vec3<T> &v)                     { return Vec3<T>(-v.x(), -v.y(), -v.z()); }
template <typename T> Vec3<T> operator* (T t, const Vec3<T> &v)                { return Vec3<T>(v.x()*t, v.y()*t, v.z()*t); }
template <typename T> Vec3<T> operator* (const Vec3<T> &v, T t)                { return Vec3<T>(v.x()*t, v.y()*t, v.z()*t); }
template <typename T> Vec3<T> operator/ (const Vec3<T> &v, T t)                { return Vec3<T>(v.x()/t, v.y()/t, v.z()/t); }
template <typename T> Vec3<T> operator+ (const Vec3<T> &v1, const Vec3<T> &v2) { return Vec3<T>(v1.x()+v2.x(), v1.y()+v2.y(), v1.z()+v2.z()); }
template <typename T> Vec3<T> operator- (const Vec3<T> &v1, const Vec3<T> &v2) { return Vec3<T>(v1.x()-v2.x(), v1.y()-v2.y(), v1.z()-v2.z()); }

template <typename T> T       operator* (const Vec3<T> &v1, const Vec3<T> &v2) { return (v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z()); }
template <typename T> Vec3<T> operator% (const Vec3<T> &v1, const Vec3<T> &v2) { return Vec3<T>(v1.y()*v2.z() - v1.z()*v2.y(), v1.z()*v2.x() - v1.x()*v2.z(), v1.x()*v2.y() - v1.y()*v2.x()); }

template <typename T> bool operator== (const Vec3<T> &v1, const Vec3<T> &v2) { return ((v1.x() == v2.x()) && (v1.y() == v2.y()) && (v1.z() == v2.z())); }
template <typename T> bool operator!= (const Vec3<T> &v1, const Vec3<T> &v2) { return ((v1.x() != v2.x()) || (v1.y() != v2.y()) || (v1.z() != v2.z())); }

template <typename T> Vec3<T> unit (const Vec3<T> &v) { return Vec3<T>(v).normalize(); }

inline float            mag   (const Vec3<float> &v) { return sqrtf(v.x()*v.x() + v.y()*v.y() + v.z()*v.z()); }
template <typename T> T mag   (const Vec3<T> &v)     { return sqrt(v.x()*v.x() + v.y()*v.y() + v.z()*v.z()); }
template <typename T> T sqmag (const Vec3<T> &v)     { return (v.x()*v.x() + v.y()*v.y() + v.z()*v.z()); }

template<typename T>
class Vec4
{
public:
	Vec4()
	{
		m_v[0] = m_v[1] = m_v[2] = m_v[3] = 0;
	}

	Vec4 (T x, T y, T z, T w)
	{
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z;
		m_v[3] = w;
	}

	Vec4 &set (T x, T y, T z, T w)
	{
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z;
		m_v[3] = w;
		return (*this);
	}

	T &operator [] (unsigned int i)
	{
		return m_v[i];
	}

	const T &operator [] (unsigned int i) const
	{
		return m_v[i];
	}

	T & x ()
	{
		return m_v[0];
	}

	const T & x () const
	{
		return m_v[0];
	}

	T & y ()
	{
		return m_v[1];
	}

	const T & y () const
	{
		return m_v[1];
	}

	T & z ()
	{
		return m_v[2];
	}

	const T & z () const
	{
		return m_v[2];
	}

	T & w ()
	{
		return m_v[3];
	}

	const T & w () const
	{
		return m_v[3];
	}

	Vec4 &operator += (const Vec4 &v)
	{
		m_v[0] += v[0];
		m_v[1] += v[1];
		m_v[2] += v[2];
		m_v[3] += v[3];
		return (*this);
	}

	Vec4 &operator -= (const Vec4 &v)
	{
		m_v[0] -= v[0];
		m_v[1] -= v[1];
		m_v[2] -= v[2];
		m_v[3] -= v[3];
		return (*this);
	}
		
	Vec4 &operator *= (T t)
	{
		m_v[0] *= t;
		m_v[1] *= t;
		m_v[2] *= t;
		m_v[3] *= t;
		return (*this);
	}
		
	Vec4 &operator /= (T t)
	{
		T f = 1.0f / t;
		m_v[0] *= f;
		m_v[1] *= f;
		m_v[2] *= f;
		m_v[3] *= f;
		return (*this);
	}

	Vec4 &normalize ()
	{
		T f = 1.0f / mag(*this);
		m_v[0] *= f;
		m_v[1] *= f;
		m_v[2] *= f;
		m_v[3] *= f;
		return (*this);
	}

	T * ptr()
	{
		return m_v;
	}

	const T * ptr() const
	{
		return m_v;
	}

private:
	T m_v[4];
};

template <typename T> Vec4<T> operator- (const Vec4<T> &v)                     { return Vec4<T>(-v.x(), -v.y(), -v.z(), -v.w()); }
template <typename T> Vec4<T> operator* (T t, const Vec4<T> &v)                { return Vec4<T>(v.x()*t, v.y()*t, v.z()*t, v.w()*t); }
template <typename T> Vec4<T> operator* (const Vec4<T> &v, T t)                { return Vec4<T>(v.x()*t, v.y()*t, v.z()*t, v.w()*t); }
template <typename T> Vec4<T> operator/ (const Vec4<T> &v, T t)                { return Vec4<T>(v.x()/t, v.y()/t, v.z()/t, v.w()/t); }
template <typename T> Vec4<T> operator+ (const Vec4<T> &v1, const Vec4<T> &v2) { return Vec4<T>(v1.x()+v2.x(), v1.y()+v2.y(), v1.z()+v2.z(), v1.w()+v2.w()); }
template <typename T> Vec4<T> operator- (const Vec4<T> &v1, const Vec4<T> &v2) { return Vec4<T>(v1.x()-v2.x(), v1.y()-v2.y(), v1.z()-v2.z(), v1.w()-v2.w()); }

template <typename T> T operator* (const Vec4<T> &v1, const Vec4<T> &v2) { return (v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z() + v1.w()*v2.w()); }

template <typename T> bool operator== (const Vec4<T> &v1, const Vec4<T> &v2) { return ((v1.x() == v2.x()) && (v1.y() == v2.y()) && (v1.z() == v2.z()) && (v1.w() == v2.w())); }
template <typename T> bool operator!= (const Vec4<T> &v1, const Vec4<T> &v2) { return ((v1.x() != v2.x()) || (v1.y() != v2.y()) || (v1.z() != v2.z()) || (v1.w() != v2.w())); }

template <typename T> Vec4<T> unit (const Vec4<T> &v) { return Vec4<T>(v).normalize(); }

inline float            mag   (const Vec4<float> &v) { return sqrtf(v.x()*v.x() + v.y()*v.y() + v.z()*v.z() + v.w()*v.w()); }
template <typename T> T mag   (const Vec4<T> &v)     { return sqrt(v.x()*v.x() + v.y()*v.y() + v.z()*v.z() + v.w()*v.w()); }
template <typename T> T sqmag (const Vec4<T> &v)     { return (v.x()*v.x() + v.y()*v.y() + v.z()*v.z() + v.w()*v.w()); }

typedef Vec2<unsigned int> Vec2ui;
typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

typedef Vec3<unsigned int> Vec3ui;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

typedef Vec4<unsigned int> Vec4ui;
typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;

};

#endif
