#pragma once

#define _USE_MATH_DEFINES

#include "Vector3.h"
#include "Matrix4f.h"
#include "Shader.h"
#include "Material.h"
#include <cmath>

class Objects;

class Object
{
public:

	enum class ShaderType {LAMP, LIGHTING};

	Object() = default;
	Object(Vector3 const& position, float size, Vector3 const& diffuse, Vector3 const& specular, float shininess, float mass,
		Vector3 const& velocity);
	Object(Vector3 const& position, float size, float shininess, float mass, Vector3 const& velocity);
	Object(Vector3 const& position, float size, float mass, Vector3 const& velocity);
	float getRadians(float degreeAngle);
	Vector3 getPosition();
	//virtual bool intersect(Objects const& objects) = 0;
	//virtual bool intersectRay(int x, int y, Camera const& camera) = 0;
	float getSize();
	void setSize(float size);
	void updateVelocityAndPosition(float dt);
	void setPosition(Vector3 const& position);
	virtual void draw(Shader const& shader, Object::ShaderType shaderType) = 0;

protected:
	Vector3 m_force;
	Vector3 m_velocity;
	float m_mass;
	Material m_material;
	bool m_isTexture;
	Vector3 m_diffuse;
	Vector3 m_specular;
	float m_shininess;
	Vector3 m_position;
	float m_size;
};