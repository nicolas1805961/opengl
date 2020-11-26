#pragma once

#include "Light.h"
#include "Vector3.h"
#include <memory>
#include "Object.h"

class Lamp: public Light
{
public:
	Lamp(Shader const& shader1, Shader const& shader2, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
		std::shared_ptr<Object> const& shape);
	std::shared_ptr<Object> getShape();
	
private:
	std::shared_ptr<Object> m_shape;
};
