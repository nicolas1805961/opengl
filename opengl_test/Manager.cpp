#include "Manager.h"

Manager::Manager(bool nightVisionOn): m_nightVisionOn(nightVisionOn), m_time(0.0)
{
	m_shaders = std::set<Shader>();
	m_objects = ObjectType();
	m_intersections = intersectionType();
	m_frameBuffers = std::unordered_map<std::string, FrameBuffer>();
}

void Manager::addShader(Shader const& shader)
{
	m_shaders.insert(shader);
}


void Manager::addObject(std::shared_ptr<Object> const& object, Shape const& shape)
{
	m_objects[shape].insert(object);
}

void Manager::addObjectIntersection(std::shared_ptr<Object> const& object, Plane const& plane)
{
	m_intersections[plane].insert(object);
}

void Manager::testIntersection(float dt)
{
	for (auto const& it : m_intersections)
	{
		for (auto const& it2 : it.second)
		{
			if (it2->intersectPlane(it.first))
				it2->reset();
			else
				it2->updateVelocityAndPosition(dt);
		}
	}
}

std::set<Shader> Manager::getShaders()
{
	return m_shaders;
}

Manager::ObjectType Manager::getObjects()
{
	return m_objects;
}

/*void Manager::drawDay(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowViewProjMatrices,
	Shader const& dayShader, Shader const& shadowShader, FrameBuffer const& frameBuffer)
{
	frameBuffer.bind();
	draw(shadowViewProjMatrices, shadowShader, frameBuffer.getId());
	frameBuffer.unbind();
	frameBuffer.bindTexture();
	draw(viewProjMatrices, shadowViewProjMatrices, dayShader, 0);
	frameBuffer.unbindTexture();
}

void Manager::drawNight(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowViewProjMatrices,
	Shader const& dayShader, Shader const& lampShader, Shader const& shadowShader, FrameBuffer const& frameBuffer)
{
	frameBuffer.bind();
	draw(shadowViewProjMatrices, shadowShader, frameBuffer.getId());
	frameBuffer.unbind();
	frameBuffer.bindTexture();
	draw(viewProjMatrices, shadowViewProjMatrices, dayShader, 0);
	frameBuffer.unbindTexture();
	draw(viewProjMatrices, lampShader, 0);
}



void Manager::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader, unsigned int frameBufferId)
{
	if (frameBufferId == 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_DEPTH_BUFFER_BIT);
	myMaps::iterator it;
	if (shader.getShaderType() == Shader::ShaderType::DEPTH)
		it = std::find_if(m_objects.begin(), m_objects.end(), [](auto x) {return x.first.getShaderType() == Shader::ShaderType::LIGHTING; });
	else
		it = std::find_if(m_objects.begin(), m_objects.end(), [](auto x) {return x.first.getShaderType() == Shader::ShaderType::LAMP; });
	if (it != m_objects.end())
	{
		shader.bind();
		for (auto const& it1 : it->second)
		{
			it1.first.second.bind();
			it1.first.first.bind();
			for (auto const& it2 : it1.second)
			{
				it2.second->draw(viewProjMatrices, it1.first.first.getCount(), shader);
			}
		}
	}
	else
		std::cout << "ERROR\n";
}

void Manager::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader, unsigned int frameBufferId) const
{
	if (frameBufferId == 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_DEPTH_BUFFER_BIT);
	myMaps::const_iterator it;
	if (shader.getShaderType() == Shader::ShaderType::DEPTH)
		it = std::find_if(m_objects.begin(), m_objects.end(), [](auto x) {return x.first.getShaderType() == Shader::ShaderType::LIGHTING; });
	else
		it = std::find_if(m_objects.begin(), m_objects.end(), [](auto x) {return x.first.getShaderType() == Shader::ShaderType::LAMP; });
	if (it != m_objects.end())
	{
		shader.bind();
		for (auto const& it1 : it->second)
		{
			it1.first.second.bind();
			it1.first.first.bind();
			for (auto const& it2 : it1.second)
			{
				it2.second->draw(viewProjMatrices, it1.first.first.getCount(), shader);
			}
		}
	}
	else
		std::cout << "ERROR\n";
}

void Manager::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
	Shader const& shader, unsigned int frameBufferId)
{
	if (frameBufferId == 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_DEPTH_BUFFER_BIT);
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [](auto x) {return x.first.getShaderType() == Shader::ShaderType::LIGHTING; });
	if (it != m_objects.end())
	{
		shader.bind();
		for (auto const& it1 : it->second)
		{
			it1.first.second.bind();
			it1.first.first.bind();
			for (auto const& it2 : it1.second)
			{
				it2.second->draw(viewProjMatrices, shadowMatrices, it1.first.first.getCount(), shader);
			}
		}
	}
	else
		std::cout << "ERROR\n";
}*/

void Manager::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices, bool night,
	Shape const& screenData, Shader const& screenShader)
{
	m_frameBuffers["sceneFrameBuffer"].bind();
	glEnable(GL_DEPTH_TEST);
	if (night)
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& it : m_shaders)
		{
			it.bind();
			if (it.getShaderType() == Shader::ShaderType::LIGHTING)
				drawLighting(viewProjMatrices, shadowMatrices, it);
			else if (it.getShaderType() == Shader::ShaderType::LAMP)
				drawLamp(viewProjMatrices, it);
		}
	}
	else
	{
		glClearColor(0.37f, 0.65f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& it : m_shaders)
		{
			it.bind();
			if (it.getShaderType() == Shader::ShaderType::DEPTH)
				drawShadow(shadowMatrices, it);
			else if (it.getShaderType() == Shader::ShaderType::LIGHTING)
				drawLighting(viewProjMatrices, shadowMatrices, it);
		}
	}
	m_frameBuffers["sceneFrameBuffer"].unbind();
	glClear(GL_COLOR_BUFFER_BIT);
	screenShader.bind();
	screenShader.set_uniform_1i("nightVisionOn", m_nightVisionOn);
	screenShader.set_uniform_1f("time", m_time);
	screenData.getVertexArray().bind();
	m_frameBuffers["sceneFrameBuffer"].bindTexture();
	glDisable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, screenData.getIndexCount(), GL_UNSIGNED_INT, nullptr);
	m_frameBuffers["sceneFrameBuffer"].unbindTexture();
}

void Manager::drawLighting(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
	Shader const& shader)
{
	m_frameBuffers["shadowFrameBuffer"].bindTexture();
	for (auto& it1 : m_objects)
	{
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			if (!it2->isLamp())
				it2->drawLighting(viewProjMatrices, shadowMatrices, it1.first.getIndexCount(), shader);
		}
	}
	m_frameBuffers["shadowFrameBuffer"].unbindTexture();
}

void Manager::addFrameBuffer(std::string const& name, FrameBuffer const& frameBuffer)
{
	m_frameBuffers[name] = frameBuffer;
}

void Manager::drawLamp(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader)
{
	for (auto& it1 : m_objects)
	{
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			if (it2->isLamp())
				it2->drawLamp(viewProjMatrices, it1.first.getIndexCount(), shader);
		}
	}
}

void Manager::drawShadow(std::pair<Matrix4f, Matrix4f> const& shadowMatrices, Shader const& shader)
{
	m_frameBuffers["shadowFrameBuffer"].bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& it1 : m_objects)
	{
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			if (!it2->isLamp())
				it2->drawShadow(shadowMatrices, it1.first.getIndexCount(), shader);
		}
	}
	//m_frameBuffers["shadowFrameBuffer"].unbind();
	m_frameBuffers["sceneFrameBuffer"].bind();
}

bool Manager::trace(Ray& ray)
{
	for (auto const& it1 : m_objects)
	{
		for (auto const& it2 : it1.second)
		{
			if (it2->intersectRay(ray))
			{
				if (ray.get_t_distance() < ray.get_nearest())
				{
					ray.set_nearest(ray.get_t_distance());
					ray.set_hit(it2);
				}
			}
		}
	}
	ray.set_t_distance(ray.get_nearest());
	return (ray.get_hit() != nullptr);
}

void Manager::getSizeShaders()
{
	unsigned int size = 0;
	for (auto it : m_shaders)
		size++;
	std::cout << size << "\n";
}

void Manager::getSizeObjects()
{
	unsigned int size = 0;
	for (auto it : m_objects)
	{
		for (auto it2 : it.second)
			size++;
	}
	std::cout << size << "\n";
}

void Manager::keepTrack()
{
	for (auto const& it : m_objects)
	{
		for (auto const& it2 : it.second)
		{
			it2->keepTrack();
		}
	}
}

Manager::intersectionType Manager::getIntersections()
{
	return m_intersections;
}

void Manager::toggleNightVision()
{
	m_nightVisionOn = !m_nightVisionOn;
}

void Manager::setElapsedTime(float time)
{
	m_time = time;
}

/*void Manager::resetFirstPosition()
{
	for (auto const& it : m_intersections)
	{
		for (auto const& it2 : it.second)
		{
			it2->setTranslation(it2->getFirstPosition());
			it2->setPosition(it2->getFirstPosition());
		}
	}
}*/
