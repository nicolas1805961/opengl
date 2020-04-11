#pragma once

#define _USE_MATH_DEFINES

#include "Vector3.h"
#include "Matrix4f.h"
#include "Shader.h"
#include "Material.h"
#include <cmath>
#include "Camera.h"

class Objects;

class Ray;

class Object
{
public:

	enum class objectType {PLANE, SPHERE, CUBE};

	enum class Force {GRAVITY, FRICTION};

	Object() = default;
	Object(Shader const& shader, Vector3 const& translation, float scale, Vector3 const& diffuse, Vector3 const& specular, float shininess,
		float mass, Vector3 const& velocity);
	Object(Shader const& shader, Vector3 const& translation, float scale, float shininess, float mass, Vector3 const& velocity);
	float getRadians(float degreeAngle);
	Shader getShader() const;
	Shader getShader();
	Vector3 getTranslation();
	Vector3 getTranslation() const;
	void keepTrack(Matrix4f const& model, Matrix4f const& view, Matrix4f const& projection);
	virtual bool intersectRay(Ray &ray) = 0;
	//virtual bool intersectRay(int x, int y, Camera const& camera) = 0;
	float getScale();
	void addForce(Force force);
	void setColor(Vector3 const& color);
	void setScale(float scale);
	void updateVelocityAndPosition(float dt);
	void setTranslation(Vector3 const& translation);
	virtual void draw(Matrix4f const& view, Matrix4f const& projection, unsigned int indexCount) = 0;

protected:
	Shader m_shader;
	bool m_doesModify;
	Vector4 m_position;
	Vector3 m_sumForces;
	Vector3 m_acceleration;
	Vector3 m_velocity;
	float m_mass;
	Material m_material;
	bool m_isTexture;
	Vector3 m_diffuse;
	Vector3 m_specular;
	float m_shininess;
	Vector3 m_translation;
	float m_scale;
};