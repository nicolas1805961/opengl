#pragma once

#include <map>
#include "Object.h"
#include <memory>
#include <string>
#include "Cube.h"
#include "Sphere.h"
#include <utility>
#include <algorithm>
#include "FrameBuffer.h"
#include <unordered_set>
#include <set>
#include <unordered_map>
#include "Shape.h"
#include "FrameBuffer.h"
#include "SSBO.h"

struct MyHashMap
{
	std::size_t operator()(Shape const& s) const
	{
		std::size_t h1 = std::hash<unsigned int>{}(s.getIndexCount());
		std::size_t h2 = std::hash<unsigned int>{}(s.getVertexArray().getId());
		return h1 ^ (h2 << 1);
	}
};

struct MyHashMapIntersection
{
	std::size_t operator()(Plane const& s) const
	{
		std::size_t h1 = std::hash<unsigned int>{}(s.getNormal().get_x());
		std::size_t h2 = std::hash<unsigned int>{}(s.getNormal().get_y());
		return h1 ^ (h2 << 1);
	}
};

struct MyHashSet
{
	std::size_t operator()(std::shared_ptr<Object> const& s) const
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

struct MyComparatorMapFrameBuffer
{
	bool operator()(FrameBuffer const& left, FrameBuffer const& right) const
	{
		return left.getId() == right.getId();
	}
};

struct MyHashMapFrameBuffer
{
	std::size_t operator()(FrameBuffer const& s) const
	{
		std::size_t h1 = std::hash<float>{}(s.getId());
		std::size_t h2 = std::hash<float>{}(s.getTexture().getId());
		return h1 ^ (h2 << 1);
	}
};

class Manager
{
public:

	using ObjectType = std::unordered_map<Shape, std::unordered_set<std::shared_ptr<Object>, MyHashSet, MyComparatorSet>, MyHashMap, MyComparatorMap>;
	using intersectionType = std::unordered_map<Plane, std::unordered_set<std::shared_ptr<Object>, MyHashSet, MyComparatorSet>, MyHashMapIntersection, MyComparatorMapIntersection>;

	Manager(bool nightVisionOn, bool night, float grass_height);
	void addShader(Shader const& shader);
	void addObject(std::shared_ptr<Object> const& object, Shape const& shape);
	void addObjectIntersection(std::shared_ptr<Object> const& object, Plane const& plane);
	void testIntersection(float dt);
	std::set<Shader> getShaders();
	ObjectType getObjects();
	void draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		Shape const& screenData, Shader const& screenShader, SSBO const& particleData, SSBO const& particleData2D);
	void drawShadow(std::pair<Matrix4f, Matrix4f> const& shadowMatrices, Shader const& shader);
	void drawLighting(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		Shader const& shader);
	void drawGrass(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		Shader const& shader);
	void drawNormal(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader);
	void drawParticles(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, SSBO const& particleData, Shader const& shader);
	void drawParticles2D(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, SSBO const& particleData, Shader const& shader);
	void addFrameBuffer(std::string const& name, FrameBuffer const& frameBuffer);
	bool trace(Ray& ray);
	void getSizeShaders();
	void getSizeObjects();
	void keepTrack();
	intersectionType getIntersections();
	void toggleNightVision();
	void toggleNight();
	void toggleRain();
	void increase_grass_height(float x);
	void decrease_grass_height(float x);
	bool isNight();
	void setElapsedTime(float time);
	void set_normals();
	void set_dt(float dt);
	//void resetFirstPosition();

private:
	static int m_placesLeft;
	std::set<Shader> m_shaders;
	ObjectType m_objects;
	intersectionType m_intersections;
	std::unordered_map<std::string, FrameBuffer> m_frameBuffers;
	bool m_nightVisionOn;
	float m_time;
	float m_dt;
	bool m_night;
	float m_grass_height;
	bool m_show_normals;
	bool m_rain;
};