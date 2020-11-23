#pragma once

#include <random>
#include "Object.h"
#include "VertexArray.h"

class Grass: public Object
{
public:
	Grass();
	Grass(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, float scale = 1.0f,
		bool isLamp = false, float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), bool light = false, float shininess = 32.0f);
	Grass(std::string const& name, Vector3 const& translation, bool isLamp = false, float scale = 1.0f, float degreeAngle = 0.0f,
		Vector3 const& axis = Vector3(1.0f), bool light = false, float shininess = 32.0f);
	static std::pair<VertexArray, unsigned int> initializeLayout();
	bool intersectRay(Ray& ray);
	bool intersectPlane(Plane const& plane);
	void keepTrack();

private:

};

