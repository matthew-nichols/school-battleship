#ifndef IDKNOTI_VECTOR
#define IDKNOTI_VECTOR

#include <cmath>

namespace Idknoti
{

using namespace std;

// vector of space N and type T

template<int N, class T>
class Vector
{
private:
	T _elem[N];
public:
	Vector()
	{
		for (int i = 0; i < N; i++)
			_elem[i] = 0;
	}

	Vector(const Vector<N, T>& v)
	{
		for (int i = 0; i < N; i++)
			_elem[i] = v[i];
	}

	const T& operator[](int i) const { return _elem[i]; }
	T& operator[](int i) const { return _elem[i]; }

	const T mag2() const { return ::mag2(*this); }
	const T mag() const { return ::mag(*this); }

};

template<class T>
class Vector<2, T>
{
private:
	T _elem[2];
public:
	Vector() { _elem[0] = _elem[1] = 0; }
	Vector(const Vector<2, T>& v) { _elem[0] = v.x(), _elem[1] = v.y(); }
	Vector(T x, T y) { _elem[0] = x; _elem[1] = y; }

	const T& x() const { return _elem[0]; }
	T& x() { return _elem[0]; }
	const T& y() const { return _elem[1]; }
	T& y() { return _elem[1]; }

	T& operator[] (int i) { return _elem[i]; }
	const T& operator[] (int i) const { return _elem[i]; }

	const T mag2() const { return ::mag2(*this); }
	const T mag() const { return ::mag(*this); }

	template<class T2>
	operator Vector<2, T2>() const { //return vecConv<2, T, T2>(*this); }
		return Vector<2, T2>((T2)x(), (T2)y());}
};

template<class T>
class Vector<3, T>
{
private:
	T _elem[3];
public:
	Vector() { _elem[0] = _elem[1] = _elem[2] = 0; }
	Vector(const Vector<3, T>& v) { _elem[0] = v.x(); _elem[1] = v.y(); _elem[2] = v.z(); }
	Vector(T x, T y, T z) { _elem[0] = x; _elem[1] = y; _elem[2] = z; }

	const T& x() const { return _elem[0]; }
	T& x() { return _elem[0]; }
	const T& y() const { return _elem[1]; }
	T& y() { return _elem[1]; }
	const T& z() const { return _elem[2]; }
	T& z() { return _elem[2]; }

	const T& operator[] (int i) const { return _elem[i]; }
	T& operator[] (int i ) { return _elem[i]; }

	const T mag2() const { return ::mag2(*this); }
	const T mag() const { return ::mag(*this); }
};

// cross product for 3-space
template<class T>
const Vector<3, T> operator% (const Vector<3, T>& v1, const Vector<3, T>& v2)
{
	return Vector<3, T>(v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x());
}

// operators common to all vectors
// compiler should optimize this; if not, specializations can be used

template<int N, class T>
const Vector<N, T> operator* (const Vector<N, T>& v, const T s)
{
	Vector<N, T> ret;
	for (int i = 0; i < N; i++)
		ret[i] = v[i] * s;
	return ret;
}

template<int N, class T>
const Vector<N, T> operator* (const T s, const Vector<N, T>& v)
{
	Vector<N, T> ret;
	for (int i = 0; i < N; i++)
		ret[i] = s * v[i];
	return ret;
}

template<int N, class T>
const Vector<N, T> operator/ (const Vector<N, T>& v, const T s)
{
	Vector<N, T> ret;
	for (int i = 0; i < N; i++)
		ret[i] = v[i] / s;
	return ret;
}

template<int N, class T>
const Vector<N, T> operator- (const Vector<N, T>& v)
{
	Vector<N, T> ret;
	for (int i = 0; i < N; i++)
		ret[i] = - v[i];
	return ret;
}

template<int N, class T>
const Vector<N, T> operator+ (const Vector<N, T>& v1, const Vector<N, T>& v2)
{
	Vector<N, T> ret;
	for (int i = 0; i < N; i++)
		ret[i] = v1[i] + v2[i];
	return ret;
}

template<int N, class T>
const Vector<N, T> operator- (const Vector<N, T>& v1, const Vector<N, T>& v2)
{
	return v1 + (-v2);
}

template<int N, class T>
const T operator* (const Vector<N, T>& v1, const Vector<N, T>& v2)
{
	T ret = 0;
	for (int i = 0; i < N; i++)
		ret += v1[i] * v2[i];
	return ret;
}

template<int N, class T>
Vector<N, T>& operator+= (Vector<N, T>& v1, const Vector<N, T>& v2)
{
	v1 = v1 + v2;
	return v1;
}

template<int N, class T>
Vector<N, T>& operator-= (Vector<N, T>& v1, const Vector<N, T>& v2)
{
	v1 = v1 - v2;
	return v1;
}

template<int N, class T>
const T mag2(const Vector<N, T>& v)
{
	return v * v;
}

template<int N, class T>
const T mag(const Vector<N, T>& v)
{
	return sqrt(mag2(v));
}

template<int N, class T, class T2>
Vector<N, T> vecConv(const Vector<N, T2>& v)
{
	Vector<N, T> ret;
	for (int i = 0; i < N; i++)
		ret[i] = (T)(v[i]);
	return ret;
}

template<int N, class T>
Vector<N, T> unitVec(const Vector<N, T>& v) { return v / v.mag(); }

typedef Vector<2, float> Vec2f;
typedef Vector<2, double> Vec2;
typedef Vector<2, int> Vec2i;

typedef Vector<3, float> Vec3f;
typedef Vector<3, double> Vec3;
typedef Vector<3, int> Vec3i;

typedef Vector<4, float> Vec4f;
typedef Vector<4, double> Vec4;
typedef Vector<4, int> Vec4i;

}

#endif
