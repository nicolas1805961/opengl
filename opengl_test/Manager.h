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
#include "FrameBuffer.h"
#include <unordered_set>
#include <set>
#include <unordered_map>
#include "Shape.h"

struct MyHashMap
{
	std::size_t operator()(Shape const& s) const noexcept
	{
		std::size_t h1 = std::hash<unsigned int>{}(s.getIndexBuffer().getId());
		std::size_t h2 = std::hash<unsigned int>{}(s.getVertexArray().getId());
		return h1 ^ (h2 << 1);
	}
};

struct MyHashSet
{
	std::size_t operator()(std::shared_ptr<Object> const& s) const noexcept
	{
		std::size_t h1 = std::hash<float>{}(s->getTranslation().get_x());
		std::size_t h2 = std::hash<float>{}(s->getTranslation().get_y());
		return h1 ^ (h2 << 1);
	}
};

struct MyComparatorMap
{
	bool operator()(Shape const& left, Shape const& right) const
	{
		auto leftIndexBuffer = left.getIndexBuffer();
		auto rightIndexBuffer = right.getIndexBuffer();
		auto leftVertexArray = left.getVertexArray();
		auto rightVertexArray = right.getVertexArray();
		return (leftIndexBuffer.getId() == rightIndexBuffer.getId()) 
			&& (leftVertexArray.getId() == rightVertexArray.getId());
	}
};

struct MyComparatorSet
{
	bool operator()(std::shared_ptr<Object> const& left, std::shared_ptr<Object> const& right) const
	{
		return left->getName() == right->getName();
	}
};

class Manager
{
public:

	using ObjectType = std::unordered_map<Shape, std::unordered_set<std::shared_ptr<Object>, MyHashSet, MyComparatorSet>, MyHashMap, MyComparatorMap>;

	Manager();
	void addShader(Shader const& shader);
	void addObject(std::shared_ptr<Object> const& object, Shape const& shape);
	std::set<Shader> getShaders();
	ObjectType getObjects();
	void draw(FrameBuffer const& frameBuffer, std::pair<Matrix4f, Matrix4f> const& viewProjMatrices,
		std::pair<Matrix4f, Matrix4f> const& shadowMatrices, bool night);
	void drawLamp(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader);
	void drawShadow(std::pair<Matrix4f, Matrix4f> const& shadowMatrices, FrameBuffer const& frameBuffer, Shader const& shader);
	void drawLighting(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		Shader const& shader, FrameBuffer const& frameBuffer);
	bool trace(Ray& ray);
	void getSizeShaders();
	void getSizeObjects();

private:
	static int m_placesLeft;
	std::set<Shader> m_shaders;
	ObjectType m_objects;
};