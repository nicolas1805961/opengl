#pragma once

#define _USE_MATH_DEFINES

#include "Vector3.h"
#include "Matrix4f.h"
#include "Shader.h"
#include "Material.h"
#include <cmath>
#include "Camera.h"

class Manager;

class Ray;

class Object
{
public:

	enum class objectType {PLANE, SPHERE, CUBE};

	enum class Force {GRAVITY, FRICTION};

	enum class IsLamp { LAMP, NOLAMP };

	Object() = default;
	Object(std::string const& name, Vector3 const& translation, float scale, Vector3 const& diffuse, Vector3 const& specular, bool isLamp = false, float degreeAngle = 0.0f,
		Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f),
		bool doesModify = false, bool isTexture = false, Vector3 const& acceleration = Vector3(0.0f),
		Vector3 const& sumForces = Vector3(0.0f), Vector4 const& position = Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	Object(std::string const& name, Vector3 const& translation, float scale, bool isLamp = false, float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f,
		float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f), bool doesModify = false, bool isTexture = false,
		Vector3 const& acceleration = Vector3(0.0f), Vector3 const& sumForces = Vector3(0.0f),
		Vector4 const& position = Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	float getRadians(float degreeAngle);
	Vector3 getTranslation();
	Vector3 getTranslation() const;
	std::string getName();
	std::string getName() const;
	void keepTrack(Matrix4f const& model, Matrix4f const& view, Matrix4f const& projection);
	virtual bool intersectRay(Ray &ray) = 0;
	//virtual bool intersectRay(int x, int y, Camera const& camera) = 0;
	float getScale();
	void addForce(Force force);
	void setColor(Vector3 const& color);
	void setScale(float scale);
	void updateVelocityAndPosition(float dt);
	void setTranslation(Vector3 const& translation);
	void drawDay(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		unsigned int indexCount, Shader const& shader);
	void drawLamp(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader);
	void drawShadow(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader);
	void drawNight(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader);
	bool isLamp();

protected:
	std::string m_name;
	bool m_isLamp;
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
	float m_degreeAngle;
	Vector3 m_axis;
};