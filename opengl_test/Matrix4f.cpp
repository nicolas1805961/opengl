#include "Matrix4f.h"

Matrix4f::Matrix4f()
{
	m_matrix = std::vector<Vector4>(4, Vector4(0));
}

Matrix4f::Matrix4f(float f)
{
    if (f == 1.0f)
    {
	    m_matrix = std::vector<Vector4>(4, Vector4(0));
        m_matrix[0][0] = 1.0f;
        m_matrix[1][1] = 1.0f;
        m_matrix[2][2] = 1.0f;
        m_matrix[3][3] = 1.0f;
    }
    else
        m_matrix = std::vector<Vector4>(4, Vector4(f));
}

Matrix4f::Matrix4f(Vector4 const& v1, Vector4 const& v2, Vector4 const& v3, Vector4 const& v4)
{
    m_matrix = std::vector<Vector4>(4, Vector4(0));
    m_matrix[0] = v1;
    m_matrix[1] = v2;
    m_matrix[2] = v3;
    m_matrix[3] = v4;
}

Matrix4f::Matrix4f(const std::initializer_list<float>& l)
{
    auto vec = Matrix4f();
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            vec[j][i] = l.begin()[4 * i + j];
        }
    }
}

Matrix4f Matrix4f::gl_ortho(const float& left, const float& right,
    const float& bottom, const float& top,
    const float& nearVal, const float& farVal)
{
    Matrix4f ortho;
    ortho[0][0] = 2 / (right - left);
    ortho[1][1] = 2 / (top - bottom);
    ortho[2][2] = -2 / (farVal - nearVal);
    ortho[3][0] = ((right + left) / (right - left)) * -1;
    ortho[3][1] = ((top + bottom) / (top - bottom)) * -1;
    ortho[3][2] = ((farVal + nearVal) / (farVal - nearVal)) * -1;
    ortho[3][3] = 1;
    return ortho;
}

Matrix4f Matrix4f::gl_look_at(Vector3 const& eye, Vector3 const& translation, Vector3 const& up)
{
	Vector3 f((translation - eye).normalize());
	Vector3 s(f.cross_product(up).normalize());
	Vector3 u(s.cross_product(f).normalize());
	Matrix4f Result(1.0f);
	Result[0][0] = s[0];
	Result[1][0] = s[1];
	Result[2][0] = s[2];
	Result[0][1] = u[0];
	Result[1][1] = u[1];
	Result[2][1] = u[2];
	Result[0][2] = -f[0];
	Result[1][2] = -f[1];
	Result[2][2] = -f[2];
	Result[3][0] = -s.dot_product(eye);
	Result[3][1] = -u.dot_product(eye);
	Result[3][2] = f.dot_product(eye);
	return Result;
}

Matrix4f Matrix4f::gl_frustum(const float& left, const float& right,
    const float& bottom, const float& top,
    const float& nearVal, const float& farVal)
{
    Matrix4f frustum;
    frustum[0][0] = (2 * nearVal) / (right - left);
    frustum[2][0] = (right + left) / (right - left);
    frustum[1][1] = (2 * nearVal) / (top - bottom);
    frustum[2][1] = (top + bottom) / (top - bottom);
    frustum[2][2] = ((farVal + nearVal) / (farVal - nearVal)) * -1;
    frustum[3][2] = ((2 * farVal * nearVal) / (farVal - nearVal)) * -1;
    frustum[2][3] = -1;
    return frustum;
}

Matrix4f Matrix4f::gl_translate(Matrix4f const& m, Vector3 const& v)
{
    Matrix4f translation;
    translation[0][0] = 1.0f;
    translation[1][1] = 1.0f;
    translation[2][2] = 1.0f;
    translation[3][3] = 1.0f;
    translation[3][0] = v[0];
    translation[3][1] = v[1];
    translation[3][2] = v[2];
    return m * translation;
}

Matrix4f Matrix4f::gl_scale(Matrix4f& m, Vector3 const& v)
{
	Matrix4f Result(1.0f);
    Result[0][0] = v[0];
    Result[1][1] = v[1];
    Result[2][2] = v[2];
	return m * Result;
}

Matrix4f Matrix4f::gl_rotate(Matrix4f& m, float angle, Vector3 const& axis)
{
    Vector3 axes = axis.normalize();
	float const cos = cosf(angle);
	float const s = sinf(angle);

	Vector3 temp((1.0f - cos) * axes);

	Matrix4f Rotate(1.0f);
	Rotate[0][0] = cos + temp[0] * axes[0];
	Rotate[0][1] = temp[0] * axes[1] + s * axes[2];
	Rotate[0][2] = temp[0] * axes[2] - s * axes[1];

	Rotate[1][0] = temp[1] * axes[0] - s * axes[2];
	Rotate[1][1] = cos + temp[1] * axes[1];
	Rotate[1][2] = temp[1] * axes[2] + s * axes[0];

	Rotate[2][0] = temp[2] * axes[0] + s * axes[1];
	Rotate[2][1] = temp[2] * axes[1] - s * axes[0];
	Rotate[2][2] = cos + temp[2] * axes[2];

	Matrix4f Result(1.0f);
    Vector4 a = m[0] * Rotate[0][0];
    Vector4 b = m[1] * Rotate[0][1];
    Vector4 c = m[2] * Rotate[0][2];
    Vector4 d = m[0] * Rotate[1][0];
    Vector4 e = m[1] * Rotate[1][1];
    Vector4 f = m[2] * Rotate[1][2];
    Vector4 g = m[0] * Rotate[2][0];
    Vector4 h = m[1] * Rotate[2][1];
    Vector4 i = m[2] * Rotate[2][2];

	Result[0] = a + b + c;
	Result[1] = d + e + f;
	Result[2] = g + h + i;
	Result[3] = m[3];
	return Result;
}

Matrix4f Matrix4f::gl_perspective(float fovy, float aspect, float near, float far)
{
	float tanHalfFovy = tan(fovy / 2.0f);
	Matrix4f Result;
	Result[0][0] = 1.0f / (aspect * tanHalfFovy);
	Result[1][1] = 1.0f / (tanHalfFovy);
	Result[2][2] = -(far + near) / (far - near);
	Result[2][3] = -1.0f;
	Result[3][2] = -(2.0f * far * near) / (far - near);
    return Result;
}

Matrix4f Matrix4f::getComatrix()
{
    Matrix4f result;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i][j] = pow(-1, i + j) * gl_getCofactorMatrix(i, j).determinant();
        }
    }
    return result;
}

Matrix4f Matrix4f::getComatrix() const
{
	Matrix4f result;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			result[i][j] = pow(-1, i + j) * gl_getCofactorMatrix(i, j).determinant();
		}
	}
	return result;
}

Matrix3f Matrix4f::gl_getCofactorMatrix(unsigned int column, unsigned int row)
{
    Matrix3f result;
    unsigned int a = 0, b = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if (i == column)
            continue;
        for (size_t j = 0; j < 4; j++)
        {
            if (j == row)
                continue;
            result[a][b] = m_matrix[i][j];
            b++;
        }
        a++;
        b = 0;
    }
    return result;
}

Matrix3f Matrix4f::gl_getCofactorMatrix(unsigned int column, unsigned int row) const
{
	Matrix3f result;
	unsigned int a = 0, b = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (i == column)
			continue;
		for (size_t j = 0; j < 4; j++)
		{
			if (j == row)
				continue;
			result[a][b] = m_matrix[i][j];
			b++;
		}
		a++;
		b = 0;
	}
	return result;
}

float Matrix4f::determinant()
{
	float a = m_matrix[0][0] * gl_getCofactorMatrix(0, 0).determinant();
	float b = m_matrix[1][0] * -1 * gl_getCofactorMatrix(1, 0).determinant();
	float c = m_matrix[2][0] * gl_getCofactorMatrix(2, 0).determinant();
	float d = m_matrix[3][0] * -1 * gl_getCofactorMatrix(3, 0).determinant();
	return a + b + c + d;
}

float Matrix4f::determinant() const
{
	float a = m_matrix[0][0] * gl_getCofactorMatrix(0, 0).determinant();
	float b = m_matrix[1][0] * -1 * gl_getCofactorMatrix(1, 0).determinant();
	float c = m_matrix[2][0] * gl_getCofactorMatrix(2, 0).determinant();
	float d = m_matrix[3][0] * -1 * gl_getCofactorMatrix(3, 0).determinant();
	return a + b + c + d;
}

Matrix4f Matrix4f::gl_transpose()
{
    Matrix4f result;
    result.m_matrix = m_matrix;
    result[0][1] = m_matrix[1][0];
    result[0][2] = m_matrix[2][0];
    result[0][3] = m_matrix[3][0];
    result[1][0] = m_matrix[0][1];
    result[1][2] = m_matrix[2][1];
    result[1][3] = m_matrix[3][1];
    result[2][0] = m_matrix[0][2];
    result[2][1] = m_matrix[1][2];
    result[2][3] = m_matrix[3][2];
    result[3][0] = m_matrix[0][3];
    result[3][1] = m_matrix[1][3];
    result[3][2] = m_matrix[2][3];
    return result;
}

std::unique_ptr<float[]> Matrix4f::as_array()
{
    auto ptr = std::make_unique<float[]>(16);
    ptr[0] = this->m_matrix[0][0];
    ptr[1] = this->m_matrix[0][1];
    ptr[2] = this->m_matrix[0][2];
    ptr[3] = this->m_matrix[0][3];
    ptr[4] = this->m_matrix[1][0];
    ptr[5] = this->m_matrix[1][1];
    ptr[6] = this->m_matrix[1][2];
    ptr[7] = this->m_matrix[1][3];
    ptr[8] = this->m_matrix[2][0];
    ptr[9] = this->m_matrix[2][1];
    ptr[10] = this->m_matrix[2][2];
    ptr[11] = this->m_matrix[2][3];
    ptr[12] = this->m_matrix[3][0];
    ptr[13] = this->m_matrix[3][1];
    ptr[14] = this->m_matrix[3][2];
    ptr[15] = this->m_matrix[3][3];
    return ptr;
}

std::unique_ptr<float[]> Matrix4f::as_array() const
{
	auto ptr = std::make_unique<float[]>(16);
	ptr[0] = this->m_matrix[0][0];
	ptr[1] = this->m_matrix[0][1];
	ptr[2] = this->m_matrix[0][2];
	ptr[3] = this->m_matrix[0][3];
	ptr[4] = this->m_matrix[1][0];
	ptr[5] = this->m_matrix[1][1];
	ptr[6] = this->m_matrix[1][2];
	ptr[7] = this->m_matrix[1][3];
	ptr[8] = this->m_matrix[2][0];
	ptr[9] = this->m_matrix[2][1];
	ptr[10] = this->m_matrix[2][2];
	ptr[11] = this->m_matrix[2][3];
	ptr[12] = this->m_matrix[3][0];
	ptr[13] = this->m_matrix[3][1];
	ptr[14] = this->m_matrix[3][2];
	ptr[15] = this->m_matrix[3][3];
	return ptr;
}

Matrix4f Matrix4f::inverse(Matrix4f const& m)
{
	float x = 1 / m.determinant();
	return x * m.getComatrix().gl_transpose();
}

Matrix4f operator*(float x, Matrix4f const& m)
{
    Matrix4f result;
	result[0][0] = m[0][0] * x;
	result[0][1] = m[0][1] * x;
	result[0][2] = m[0][2] * x;
	result[0][3] = m[0][3] * x;
	result[1][0] = m[1][0] * x;
	result[1][1] = m[1][1] * x;
	result[1][2] = m[1][2] * x;
	result[1][3] = m[1][3] * x;
	result[2][0] = m[2][0] * x;
	result[2][1] = m[2][1] * x;
	result[2][2] = m[2][2] * x;
	result[2][3] = m[2][3] * x;
	result[3][0] = m[3][0] * x;
	result[3][1] = m[3][1] * x;
	result[3][2] = m[3][2] * x;
	result[3][3] = m[3][3] * x;
	return result;
}

Vector3& Matrix4f::operator*(Vector3& v)
{
    Vector3 res;
    res[0] = this->m_matrix[0][0] * v[0] + this->m_matrix[0][1] * v[1] + this->m_matrix[0][2] * v[2] + this->m_matrix[0][3];
    res[1] = this->m_matrix[1][0] * v[0] + this->m_matrix[1][1] * v[1] + this->m_matrix[1][2] * v[2] + this->m_matrix[1][3];
    res[2] = this->m_matrix[2][0] * v[0] + this->m_matrix[2][1] * v[1] + this->m_matrix[2][2] * v[2] + this->m_matrix[2][3];
    return res;
}

Matrix4f Matrix4f::operator*(Matrix4f const& m)
{
    Matrix4f res;
    Vector4 l1(this->m_matrix[0][0], this->m_matrix[1][0], this->m_matrix[2][0], this->m_matrix[3][0]);
    Vector4 l2(this->m_matrix[0][1], this->m_matrix[1][1], this->m_matrix[2][1], this->m_matrix[3][1]);
    Vector4 l3(this->m_matrix[0][2], this->m_matrix[1][2], this->m_matrix[2][2], this->m_matrix[3][2]);
    Vector4 l4(this->m_matrix[0][3], this->m_matrix[1][3], this->m_matrix[2][3], this->m_matrix[3][3]);
    res[0] = Vector4(l1 * m[0], l2 * m[0], l3 * m[0], l4 * m[0]);
    res[1] = Vector4(l1 * m[1], l2 * m[1], l3 * m[1], l4 * m[1]);
    res[2] = Vector4(l1 * m[2], l2 * m[2], l3 * m[2], l4 * m[2]);
    res[3] = Vector4(l1 * m[3], l2 * m[3], l3 * m[3], l4 * m[3]);
    return res;
}

Vector4 Matrix4f::operator*(Vector4 const& v)
{
	Vector4 res;
	Vector4 l1(this->m_matrix[0][0], this->m_matrix[1][0], this->m_matrix[2][0], this->m_matrix[3][0]);
	Vector4 l2(this->m_matrix[0][1], this->m_matrix[1][1], this->m_matrix[2][1], this->m_matrix[3][1]);
	Vector4 l3(this->m_matrix[0][2], this->m_matrix[1][2], this->m_matrix[2][2], this->m_matrix[3][2]);
	Vector4 l4(this->m_matrix[0][3], this->m_matrix[1][3], this->m_matrix[2][3], this->m_matrix[3][3]);
    res[0] = l1 * v;
    res[1] = l2 * v;
    res[2] = l3 * v;
    res[3] = l4 * v;
	return res;
}

Vector4 Matrix4f::operator*(Vector4 const& v) const
{
	Vector4 res;
	Vector4 l1(this->m_matrix[0][0], this->m_matrix[1][0], this->m_matrix[2][0], this->m_matrix[3][0]);
	Vector4 l2(this->m_matrix[0][1], this->m_matrix[1][1], this->m_matrix[2][1], this->m_matrix[3][1]);
	Vector4 l3(this->m_matrix[0][2], this->m_matrix[1][2], this->m_matrix[2][2], this->m_matrix[3][2]);
	Vector4 l4(this->m_matrix[0][3], this->m_matrix[1][3], this->m_matrix[2][3], this->m_matrix[3][3]);
	res[0] = l1 * v;
	res[1] = l2 * v;
	res[2] = l3 * v;
	res[3] = l4 * v;
	return res;
}

Matrix4f Matrix4f::operator*(Matrix4f const& m) const
{
	Matrix4f res;
	Vector4 l1(this->m_matrix[0][0], this->m_matrix[1][0], this->m_matrix[2][0], this->m_matrix[3][0]);
	Vector4 l2(this->m_matrix[0][1], this->m_matrix[1][1], this->m_matrix[2][1], this->m_matrix[3][1]);
	Vector4 l3(this->m_matrix[0][2], this->m_matrix[1][2], this->m_matrix[2][2], this->m_matrix[3][2]);
	Vector4 l4(this->m_matrix[0][3], this->m_matrix[1][3], this->m_matrix[2][3], this->m_matrix[3][3]);
	res[0] = Vector4(l1 * m[0], l2 * m[0], l3 * m[0], l4 * m[0]);
	res[1] = Vector4(l1 * m[1], l2 * m[1], l3 * m[1], l4 * m[1]);
	res[2] = Vector4(l1 * m[2], l2 * m[2], l3 * m[2], l4 * m[2]);
	res[3] = Vector4(l1 * m[3], l2 * m[3], l3 * m[3], l4 * m[3]);
	return res;
}

Vector4& Matrix4f::operator[](int i)
{
    return m_matrix[i];
}

Vector4 Matrix4f::operator[](int i) const
{
    return m_matrix[i];
}

std::ostream& operator<<(std::ostream& out, Matrix4f const& m)
{
    return out << m[0][0] << " " << m[1][0] << " " << m[2][0] << " " << m[3][0] << "\n"
        << m[0][1] << " " << m[1][1] << " " << m[2][1] << " " << m[3][1] << "\n"
        << m[0][2] << " " << m[1][2] << " " << m[2][2] << " " << m[3][2] << "\n"
        << m[0][3] << " " << m[1][3] << " " << m[2][3] << " " << m[3][3] << "\n";
}