#pragma once

#define _USE_MATH_DEFINES

#include "Vector3.h"
#include "Matrix4f.h"
#include "Shader.h"
#include <cmath>
#include "Camera.h"

class Plane;

class Manager;

class Ray;

class Object
{
public:

	enum class objectType {PLANE, SPHERE, CUBE};

	enum class Force {GRAVITY};

	enum class IsLamp { LAMP, NOLAMP };

	Object() = default;
	Object(std::string const& name, Vector3 const& translation, float scale, Vector3 const& diffuse, Vector3 const& specular,
		bool isLamp = false, float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f,
		float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f), bool isTexture = false, Vector3 const& acceleration = Vector3(0.0f),
		Vector3 const& sumForces = Vector3(0.0f));
	Object(std::string const& name, Vector3 const& translation, float scale, bool isLamp = false,
		float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f), bool isTexture = false, Vector3 const& acceleration = Vector3(0.0f),
		Vector3 const& sumForces = Vector3(0.0f));
	float getRadians(float degreeAngle);
	Vector3 getTranslation();
	Vector3 getTranslation() const;
	Vector4 getPosition();
	Vector4 getPosition() const;
	std::string getName();
	std::string getName() const;
	virtual bool intersectRay(Ray &ray) = 0;
	virtual bool intersectPlane(Plane const& plane) = 0;
	//virtual bool intersectRay(int x, int y, Camera const& camera) = 0;
	void setVelocity(float velocity);
	float getScale();
	void addForce(Force force);
	void setColor(Vector3 const& color);
	void setScale(float scale);
	void updateVelocityAndPosition(float dt);
	void setTranslation(Vector3 const& translation);
	void setPosition(Vector4 const& position);
	void setPosition(Vector3 const& position);
	void drawLighting(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		unsigned int indexCount, Shader const& shader);
	void drawGrass(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader);
	void drawNormal(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader);
	void drawShadow(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader);
	virtual void keepTrack();
	void reset();
	Vector3 getFirstPosition();
	bool isLamp();

protected:
	Vector3 m_firstPosition;
	Matrix4f m_model;
	std::string m_name;
	bool m_isLamp;
	Vector4 m_position;
	Vector3 m_sumForces;
	Vector3 m_acceleration;
	Vector3 m_velocity;
	float m_mass;
	bool m_isTexture;
	Vector3 m_diffuse;
	Vector3 m_specular;
	float m_shininess;
	Vector3 m_translation;
	float m_scale;
	float m_degreeAngle;
	Vector3 m_axis;
};