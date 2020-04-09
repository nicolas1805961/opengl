#pragma once

#define _USE_MATH_DEFINES

#include <ostream>
#include <vector>
#include <initializer_list>
#include <cmath>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3f.h"


class Matrix4f
{
public:
	Matrix4f();
	Matrix4f(float f);
	Matrix4f(Vector4 const& v1, Vector4 const& v2, Vector4 const& v3, Vector4 const& v4);
	Matrix4f(const std::initializer_list<float>& l);
	static Matrix4f gl_ortho(const float& left, const float& right, const float& bottom,
		const float& top, const float& nearVal, const float& farVal);
	static Matrix4f gl_look_at(Vector3 const& eye, Vector3 const& translation, Vector3 const& up);
	static Matrix4f gl_frustum(const float& left, const float& right, const float& bottom,
		const float& top, const float& nearVal, const float& farVal);
	static Matrix4f gl_translate(Matrix4f& m, Vector3 const& v);
	static Matrix4f gl_scale(Matrix4f& m, Vector3 const& v);
	static Matrix4f gl_rotate(Matrix4f& m, float angle, Vector3 const& axis);
	static Matrix4f gl_perspective(float fovy, float aspect, float near, float far);
	//static Matrix4f gl_inverse(Matrix4f const& m);
	std::unique_ptr<float[]> as_array();
	static Matrix4f inverse(Matrix4f const& m);
	Vector3& operator*(Vector3& v);
	Vector4 operator*(Vector4 const& v);
	Vector4 operator*(Vector4 const& v) const;
	Matrix4f operator*(Matrix4f const& m);
	Matrix4f operator*(Matrix4f const& m) const;
	Vector4& operator[](int i);
	Vector4 operator[](int i) const;
	friend std::ostream& operator<<(std::ostream& out, Matrix4f const& m);
	friend Matrix4f operator*(float x, Matrix4f const& m);
	
private:
	Matrix4f getComatrix();
	Matrix4f getComatrix() const;
	Matrix3f gl_getCofactorMatrix(unsigned int column, unsigned int row);
	Matrix3f gl_getCofactorMatrix(unsigned int column, unsigned int row) const;
	float determinant();
	float determinant() const;
	Matrix4f gl_transpose();
	std::vector<Vector4> m_matrix;
};