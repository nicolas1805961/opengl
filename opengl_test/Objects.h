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

class Objects
{
	using myMaps = std::map<Shader, std::map<std::pair<IndexBuffer, VertexArray>, std::map<std::string, std::shared_ptr<Object>>, comparePair>>;
public:
	Objects();
	void addObject(Shader const& shader, std::pair<IndexBuffer, VertexArray> const& pair, std::shared_ptr<Object> const& object, std::string const& name,
		bool night);
	myMaps getObjects();
	void drawDay(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowViewProjMatrices,
		Shader const& lightingShader, Shader const& shadowShader, FrameBuffer const& frameBuffer);
	void drawNight(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowViewProjMatrices,
		Shader const& lightingShader, Shader const& lampShader, Shader const& shadowShader, FrameBuffer const& frameBuffer);
	void draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader, unsigned int frameBufferId);
	void draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		Shader const& shader, unsigned int frameBufferId);
	void draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader, unsigned int frameBufferId) const;
	void clear();
	unsigned int getSize();
	unsigned int getSizeShaderMap(myMaps::iterator const& it);
	unsigned int getSize() const;
	bool trace(Ray& ray);

private:
	static int m_placesLeft;
	myMaps m_objects;
};