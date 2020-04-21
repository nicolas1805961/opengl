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
		std::size_t h1 = std::hash<unsigned int>{}(s.getIndexCount());
		std::size_t h2 = std::hash<unsigned int>{}(s.getVertexArray().getId());
		return h1 ^ (h2 << 1);
	}
};

struct MyHashMapIntersection
{
	std::size_t operator()(Plane const& s) const noexcept
	{
		std::size_t h1 = std::hash<unsigned int>{}(s.getNormal().get_x());
		std::size_t h2 = std::hash<unsigned int>{}(s.getNormal().get_y());
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
		auto leftIndexCount = left.getIndexCount();
		auto rightIndexCount = right.getIndexCount();
		auto leftVertexArray = left.getVertexArray();
		auto rightVertexArray = right.getVertexArray();
		return (leftIndexCount == rightIndexCount) 
			&& (leftVertexArray.getId() == rightVertexArray.getId());
	}
};

struct MyComparatorMapIntersection
{
	bool operator()(Plane const& left, Plane const& right) const
	{
		auto leftPosition = left.getPosition().xyz();
		auto rightPosition = right.getPosition().xyz();
		auto leftNormal = left.getNormal().xyz();
		auto rightNormal = right.getNormal().xyz();
		return (leftPosition == rightPosition)
			&& (leftNormal == rightNormal);
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
	using intersectionType = std::unordered_map<Plane, std::unordered_set<std::shared_ptr<Object>, MyHashSet, MyComparatorSet>, MyHashMapIntersection, MyComparatorMapIntersection>;

	Manager();
	void addShader(Shader const& shader);
	void addObject(std::shared_ptr<Object> const& object, Shape const& shape);
	void addObjectIntersection(std::shared_ptr<Object> const& object, Plane const& plane);
	void testIntersection(float dt);
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
	void keepTrack();
	intersectionType getIntersections();
	//void resetFirstPosition();

private:
	static int m_placesLeft;
	std::set<Shader> m_shaders;
	ObjectType m_objects;
	intersectionType m_intersections;
};