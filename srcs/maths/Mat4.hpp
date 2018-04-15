//
// Created by Marc on 12/04/2018.
//

#pragma once

#include "Vec3.hpp"
#include "Maths.hpp"
#include "Vec2.hpp"
#include "Vec4.hpp"

template <typename T>
class Mat4
{
private:
	T m_data[16];

public:
	Mat4() { for (int i = 0; i < 16; i++) m_data[i] = 0; };
	Mat4(const T *data) { for (int i = 0; i < 16; i++) m_data[i] = data[i]; }
	Mat4(const Mat4 *m) { for (int i = 0; i < 16; i++) m_data[i] = m[i]; }
	~Mat4() = default;

	Mat4 &operator=(const Mat4 *m) { for (int i = 0; i < 16; i++) m_data[i] = m[i]; return *this; }

	Mat4 identity()
	{
		Mat4 result;

		for (int i = 0; i < 16; i++)
			result.m_data[i] = 0;

		result.m_data[0 + 0 * 4] = 1;
		result.m_data[1 + 1 * 4] = 1;
		result.m_data[2 + 2 * 4] = 1;
		result.m_data[3 + 3 * 4] = 1;

		return result;
	}

	const Mat4 mul(const Mat4 &m) const
	{
		Mat4 result = Mat4().identity();

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				result.m_data[x + y * 4] = m_data[x + 0 * 4] * m.m_data[0 + y * 4] +
											m_data[x + 1 * 4] * m.m_data[1 + y * 4] +
											m_data[x + 2 * 4] * m.m_data[2 + y * 4] +
											m_data[x + 3 * 4] * m.m_data[3 + y * 4];
			}
		}
		return result;
	}

	const Mat4 operator*(const Mat4 &m2) const { return mul(m2); }

	static Mat4 translate(const T &x, const T &y, const T &z)
	{
		Mat4 result = Mat4().identity();

		result.m_data[0 + 3 * 4] = x;
		result.m_data[1 + 3 * 4] = y;
		result.m_data[2 + 3 * 4] = z;

		return result;
	}

	static Mat4 translate(const Vec3<T> &pos) { return translate(pos.getX(), pos.getY(), pos.getZ()); }

	static Mat4 rotate(Vec3<T> axis, T angle)
	{
		T rad = DTR(angle);
		Mat4 rx = Mat4().identity();
		Mat4 ry = Mat4().identity();
		Mat4 rz = Mat4().identity();

		rx.m_data[5] = cos(rad * axis.getX());
		rx.m_data[6] = -sin(rad * axis.getX());
		rx.m_data[9] = sin(rad * axis.getX());
		rx.m_data[10] = cos(rad * axis.getX());

		ry.m_data[0] = cos(rad * axis.getY());
		ry.m_data[2] = sin(rad * axis.getY());
		ry.m_data[8] = -sin(rad * axis.getY());
		ry.m_data[10] = cos(rad * axis.getY());

		rz.m_data[0] = cos(rad * axis.getZ());
		rz.m_data[1] = -sin(rad * axis.getZ());
		rz.m_data[4] = sin(rad * axis.getZ());
		rz.m_data[5] = cos(rad * axis.getZ());

		return rz * ry * rx;
	}

	static Mat4 scale(const T &x, const T &y, const T &z)
	{
		Mat4 result = Mat4().identity();

		result.m_data[0 + 0 * 4] = x;
		result.m_data[1 + 1 * 4] = y;
		result.m_data[2 + 2 * 4] = z;

		return result;
	}

	static Mat4 scale(const Vec3<T> &vec) { return scale(vec.getX(), vec.getY(), vec.getZ()); }

	static Mat4 perspective(const T &fov, const T &aspect, const T &near, const T &far)
	{
		Mat4 result = Mat4().identity();

		T fov2 = tan(DTR(fov) / 2.0);
		T r = near - far;

		result.m_data[0 + 0 * 4] = 1.0f / (fov2 * aspect);
		result.m_data[1 + 1 * 4] = 1.0f / fov2;

		result.m_data[2 + 2 * 4] = (-near - far) / r;
		result.m_data[2 + 3 * 4] = 2 * far * near / r;

		result.m_data[3 + 2 * 4] = 1;
		result.m_data[3 + 3 * 4] = 0;

		return (result);
	}

	static Mat4 orthographic(const Vec2<T> &w, const Vec2<T> &h, const Vec2<T> &d)
	{
		Mat4 result = Mat4().identity();

		result.m_data[0] = 2.0f / (w.getY() - w.getX());
		result.m_data[5] = -2.0f / (h.getX() - h.getY());
		result.m_data[10] = -2.0f / (d.getY() - d.getX());
		result.m_data[3] = -(w.getY() + w.getX()) / (w.getY() - w.getX());
		result.m_data[7] = -(h.getX() + h.getY()) / (h.getX() - h.getY());
		result.m_data[11] = -(d.getY() + d.getX()) / (d.getY() - d.getX());

		return (result);
	}

	static Vec4<T> transform(const Mat4 &m, const Vec4<T> &v)
	{
		Vec4<T> result(0, 0, 0, 0);

		result.setX(m.m_data[0] * v.getX() + m.m_data[4] * v.getY() + m.m_data[8] * v.getZ() + m.m_data[12] * v.getW());
		result.setY(m.m_data[1] * v.getX() + m.m_data[5] * v.getY() + m.m_data[9] * v.getZ() + m.m_data[13] * v.getW());
		result.setZ(m.m_data[2] * v.getX() + m.m_data[6] * v.getY() + m.m_data[10] * v.getZ() + m.m_data[14] * v.getW());
		result.setW(m.m_data[3] * v.getX() + m.m_data[7] * v.getY() + m.m_data[11] * v.getZ() + m.m_data[15] * v.getW());

		return result;
	}

	const float *getData() const { return m_data; }
};