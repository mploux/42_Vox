//
// Created by Marc on 15/04/2018.
//

#include <ostream>

template <typename T>
class Vec4
{
private:
	T	m_x, m_y, m_z, m_w;

public:
	Vec4() : Vec4(0, 0, 0, 0) {}
	Vec4(const T &x, const T &y, const T &z, const T &w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
	Vec4(const Vec4 &v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z), m_w(v.m_w) {}
	virtual ~Vec4() = default;

	Vec4 &add(const T &x, const T &y, const T &z, const T &w) { m_x += x; m_y += y; m_z += z; m_w += w; return *this; }
	Vec4 &sub(const T &x, const T &y, const T &z, const T &w) { m_x -= x; m_y -= y; m_z -= z; m_w -= w; return *this; }
	Vec4 &mul(const T &x, const T &y, const T &z, const T &w) { m_x *= x; m_y *= y; m_z *= z; m_w *= w; return *this; }
	Vec4 &div(const T &x, const T &y, const T &z, const T &w) { m_x /= x; m_y /= y; m_z /= z; m_w /= w; return *this; }

	Vec4 &add(const Vec4 &v) { return add(v.m_x, v.m_y, v.m_z, v.m_w); }
	Vec4 &sub(const Vec4 &v) { return sub(v.m_x, v.m_y, v.m_z, v.m_w); }
	Vec4 &mul(const Vec4 &v) { return mul(v.m_x, v.m_y, v.m_z, v.m_w); }
	Vec4 &div(const Vec4 &v) { return div(v.m_x, v.m_y, v.m_z, v.m_w); }

	Vec4 &operator+=(const Vec4 &v) { return add(v); }
	Vec4 &operator-=(const Vec4 &v) { return sub(v); }
	Vec4 &operator*=(const Vec4 &v) { return mul(v); }
	Vec4 &operator/=(const Vec4 &v) { return div(v); }

	Vec4 operator+(const Vec4 &v2) { return Vec4(m_x + v2.m_x, m_y + v2.m_y, m_z + v2.m_z, m_w + v2.m_w); }
	Vec4 operator-(const Vec4 &v2) { return Vec4(m_x - v2.m_x, m_y - v2.m_y, m_z - v2.m_z, m_w + v2.m_w); }
	Vec4 operator*(const Vec4 &v2) { return Vec4(m_x * v2.m_x, m_y * v2.m_y, m_z * v2.m_z, m_w + v2.m_w); }
	Vec4 operator/(const Vec4 &v2) { return Vec4(m_x / v2.m_x, m_y / v2.m_y, m_z / v2.m_z, m_w + v2.m_w); }

	Vec4 &operator=(const Vec4 &v) { m_x = v.m_x; m_y = v.m_y; m_z = v.m_z; m_w = v.m_w; return *this; }
	Vec4 &operator=(const T &v) { m_x = v; m_y = v; m_z = v; m_w = v; return *this; }

	bool operator==(const Vec4 &v) { return m_x == v.m_x && m_y == v.m_y && m_z == v.m_z && m_w == v.m_w; }

	T getX() const { return m_x; }
	T getY() const { return m_y; }
	T getZ() const { return m_z; }
	T getW() const { return m_w; }

	void setX(T x) { m_x = x; }
	void setY(T y) { m_y = y; }
	void setZ(T z) { m_z = z; }
	void setW(T w) { m_w = w; }
};

static Vec4<int> VEC4_ZERO = Vec4<int>(0, 0, 0, 0);

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec4<T> &v) { os << v.getX() << " " << v.getY() << " " << v.getZ() << " " << v.getW(); return os; }
