#pragma once

#define _USE_MATH_DEFINES

#include <ostream>
#include <vector>
#include <initializer_list>
#include <cmath>
#include "Vector3.h"
#include "Vector4.h"


class Matrix4f
{
public:
	Matrix4f();
	Matrix4f(float f);
	Matrix4f(Vector4& v1, Vector4& v2, Vector4& v3, Vector4& v4);
	Matrix4f(const std::initializer_list<float>& l);
	static Matrix4f gl_ortho(const float& left, const float& right, const float& bottom,
		const float& top, const float& nearVal, const float& farVal);
	static Matrix4f gl_look_at(Vector3 const& eye, Vector3 const& center, Vector3 const& up);
	static Matrix4f gl_frustum(const float& left, const float& right, const float& bottom,
		const float& top, const float& nearVal, const float& farVal);
	static Matrix4f gl_translate(Matrix4f& m, Vector3 const& v);
	static Matrix4f gl_scale(Matrix4f& m, Vector3 const& v);
	static Matrix4f gl_rotate(Matrix4f& m, float angle, Vector3 const& axis);
	static Matrix4f gl_perspective(float fovy, float aspect, float near, float far);
	std::unique_ptr<float[]> as_array();
	Vector3& operator*(Vector3& v);
	Matrix4f operator*(Matrix4f& m);
	Vector4& operator[](int i);
	friend std::ostream& operator<<(std::ostream& out, Matrix4f& m);
	
private:
	std::vector<Vector4> m_matrix;
};