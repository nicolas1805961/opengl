#pragma once

#include <map>
#include "Object.h"
#include <memory>
#include <string>
#include "Cube.h"
#include "Sphere.h"

class Objects
{
public:
	Objects(unsigned int maxSize);
	void addObject(std::string const& name, std::shared_ptr<Object> const& object);
	std::map<std::string, std::shared_ptr<Object>> getObjects();

private:
	unsigned int m_maxSize;
	std::map<std::string, std::shared_ptr<Object>> m_objects;
};