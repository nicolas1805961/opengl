#pragma once

#include <map>
#include "Object.h"
#include <memory>
#include <string>
#include "Cube.h"
#include "Sphere.h"
#include <utility>
#include "comparePair.h"

class Objects
{
public:
	Objects(unsigned int maxSize);
	void addObject(std::pair<IndexBuffer, VertexArray> const& pair, std::shared_ptr<Object> const& object);
	std::map<Shader, std::map<std::pair<IndexBuffer, VertexArray>, std::vector<std::shared_ptr<Object>>, comparePair>> getObjects();
	void draw(Matrix4f const& view, Matrix4f const& projection) const;
	void draw(Matrix4f const& view, Matrix4f const& projection);
	void clear();
	bool trace(Ray& ray);

private:
	unsigned int m_maxSize;
	std::map<Shader, std::map<std::pair<IndexBuffer, VertexArray>, std::vector<std::shared_ptr<Object>>, comparePair>> m_objects;
};