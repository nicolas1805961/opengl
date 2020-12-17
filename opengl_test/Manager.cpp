#include "Manager.h"

Manager::Manager(bool nightVisionOn, bool night, float grass_height): m_nightVisionOn(nightVisionOn), m_night(night), m_time(0.0), m_grass_height(grass_height), m_show_normals(false)
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

void Manager::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
	Shape const& screenData, Shader const& screenShader, SSBO const& particleData)
{
	m_frameBuffers["sceneFrameBuffer"].bind();
	glEnable(GL_DEPTH_TEST);
	if (m_night)
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& it : m_shaders)
		{
			it.bind();
			if (it.getShaderType() == Shader::ShaderType::LIGHTING)
				drawLighting(viewProjMatrices, shadowMatrices, it);
		}
	}
	else
	{
		//0.37, 0.65, 0.92
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& it : m_shaders)
		{
			it.bind();
			if (it.getShaderType() == Shader::ShaderType::DEPTH)
				drawShadow(shadowMatrices, it);
			else if (it.getShaderType() == Shader::ShaderType::LIGHTING)
				drawLighting(viewProjMatrices, shadowMatrices, it);
			else if (it.getShaderType() == Shader::ShaderType::GRASS)
			{
				it.set_uniform_1i("isFront", true);
				it.set_uniform_1f("time", m_time);
				drawGrass(viewProjMatrices, shadowMatrices, it);
				/*it.set_uniform_1i("isFront", false);
				drawGrass(viewProjMatrices, shadowMatrices, it);*/
			}
			else if (it.getShaderType() == Shader::ShaderType::NORMAL && m_show_normals)
			{
				drawNormal(viewProjMatrices, it);
				it.set_uniform_1f("time", m_time);
			}
			else if (it.getShaderType() == Shader::ShaderType::COMPUTE)
			{
				particleData.bind();
				it.set_uniform_1f("time", m_time);
				glDispatchCompute(1, 1, 1);
				glMemoryBarrier(GL_ALL_BARRIER_BITS);
			}
			else if (it.getShaderType() == Shader::ShaderType::PARTICLE)
			{
				drawParticles(viewProjMatrices, particleData, it);
			}
		}
	}
	m_frameBuffers["sceneFrameBuffer"].unbind();
	screenShader.bind();
	screenShader.set_uniform_1i("nightVisionOn", m_nightVisionOn);
	screenShader.set_uniform_1f("time", m_time);
	screenData.getVertexArray().bind();
	m_frameBuffers["sceneFrameBuffer"].bindTexture();
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
			/*if (!m_night && it2->isLamp())
				continue;*/
			shader.set_uniform_1f("time", m_time);
			it2->drawLighting(viewProjMatrices, shadowMatrices, it1.first.getIndexCount(), shader);
		}
		it1.first.getVertexArray().unbind();
	}
	m_frameBuffers["shadowFrameBuffer"].unbindTexture();
}

void Manager::drawGrass(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
	Shader const& shader)
{
	m_frameBuffers["shadowFrameBuffer"].bindTexture();
	for (auto& it1 : m_objects)
	{
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			if (!m_night && it2->isLamp())
				continue;
			shader.set_uniform_3f("light_position", -10.0, 0.3, -1.0);
			shader.set_uniform_1f("g_height", m_grass_height);
			it2->drawLighting(viewProjMatrices, shadowMatrices, it1.first.getIndexCount(), shader);
		}
		it1.first.getVertexArray().unbind();
	}
	m_frameBuffers["shadowFrameBuffer"].unbindTexture();
}

void Manager::drawNormal(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader)
{
	m_frameBuffers["shadowFrameBuffer"].bindTexture();
	for (auto& it1 : m_objects)
	{
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			/*if (!m_night && it2->isLamp())
				continue;*/
			shader.set_uniform_3f("light_position", -10.0, 0.3, -1.0);
			shader.set_uniform_1f("g_height", m_grass_height);
			it2->drawNormal(viewProjMatrices, it1.first.getIndexCount(), shader);
		}
	}
	m_frameBuffers["shadowFrameBuffer"].unbindTexture();
}

void Manager::drawParticles(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, SSBO const& particleData, Shader const& shader)
{
	glEnable(GL_PROGRAM_POINT_SIZE);
	auto nb_particles = particleData.activate_vbo();
	glBindBuffer(GL_ARRAY_BUFFER, particleData.getId());
	shader.set_uniform_mat_4f("view", viewProjMatrices.first);
	shader.set_uniform_mat_4f("projection", viewProjMatrices.second);
	glDrawArrays(GL_POINTS, 0, nb_particles);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void Manager::addFrameBuffer(std::string const& name, FrameBuffer const& frameBuffer)
{
	m_frameBuffers[name] = frameBuffer;
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

void Manager::toggleNight()
{
	m_night = !m_night;
}

void Manager::increase_grass_height(float x)
{
	m_grass_height += x;
}

void Manager::decrease_grass_height(float x)
{
	m_grass_height -= x;
}

bool Manager::isNight()
{
	return m_night;
}

void Manager::setElapsedTime(float time)
{
	m_time = time;
}

void Manager::set_normals()
{
	m_show_normals = !m_show_normals;
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
