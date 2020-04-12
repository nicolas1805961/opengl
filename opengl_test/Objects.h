#pragma once

#include <map>
#include "Object.h"
#include <memory>
#include <string>
#include "Cube.h"
#include "Sphere.h"
#include <utility>
#include "comparePair.h"
#include <algorithm>

class Objects
{
	using myMaps = std::map<Shader, std::map<std::pair<IndexBuffer, VertexArray>, std::map<std::string, std::shared_ptr<Object>>, comparePair>>;
public:
	Objects(unsigned int maxSize);
	void addObject(std::pair<IndexBuffer, VertexArray> const& pair, std::shared_ptr<Object> const& object, std::string const& name,
		bool night);
	myMaps getObjects();
	void draw(Matrix4f const& view, Matrix4f const& projection, bool night);
	void clear();
	unsigned int getSize();
	unsigned int getSizeShaderMap(myMaps::iterator const& it);
	unsigned int getSize() const;
	bool trace(Ray& ray);

private:
	static int m_placesLeft;
	unsigned int m_maxSize;
	myMaps m_objects;
};