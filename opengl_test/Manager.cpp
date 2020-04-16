#include "Manager.h"

int Manager::m_placesLeft = 7;

Manager::Manager()
{
	m_shaders = std::set<Shader>();
	m_objects = ObjectType();
}

void Manager::addShader(Shader const& shader)
{
	m_shaders.insert(shader);
}


void Manager::addObject(std::shared_ptr<Object> const& object, Shape const& shape)
{
	m_objects[shape].insert(object);
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

void Manager::draw(FrameBuffer const& frameBuffer, std::pair<Matrix4f, Matrix4f> const& viewProjMatrices,
	std::pair<Matrix4f, Matrix4f> const& shadowMatrices, bool night)
{
	if (night)
	{
		for (auto& it : m_shaders)
		{
			it.bind();
			if (it.getShaderType() == Shader::ShaderType::LIGHTING)
				drawLighting(viewProjMatrices, shadowMatrices, it, frameBuffer);
			else if (it.getShaderType() == Shader::ShaderType::LAMP)
				drawLamp(viewProjMatrices, it);
		}
	}
	else
	{
		for (auto& it : m_shaders)
		{
			it.bind();
			if (it.getShaderType() == Shader::ShaderType::DEPTH)
				drawShadow(shadowMatrices, frameBuffer, it);
			else if (it.getShaderType() == Shader::ShaderType::LIGHTING)
				drawLighting(viewProjMatrices, shadowMatrices, it, frameBuffer);
		}
	}
}

void Manager::drawLighting(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
	Shader const& shader, FrameBuffer const& frameBuffer)
{
	frameBuffer.bindTexture();
	for (auto& it1 : m_objects)
	{
		it1.first.getIndexBuffer().bind();
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			if (!it2->isLamp())
				it2->drawDay(viewProjMatrices, shadowMatrices, it1.first.getIndexBuffer().getCount(), shader);
		}
	}
	frameBuffer.unbindTexture();
}

void Manager::drawLamp(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader)
{
	for (auto& it1 : m_objects)
	{
		it1.first.getIndexBuffer().bind();
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			if (it2->isLamp())
				it2->drawLamp(viewProjMatrices, it1.first.getIndexBuffer().getCount(), shader);
		}
	}
}

void Manager::drawShadow(std::pair<Matrix4f, Matrix4f> const& shadowMatrices, FrameBuffer const& frameBuffer, Shader const& shader)
{
	frameBuffer.bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& it1 : m_objects)
	{
		it1.first.getIndexBuffer().bind();
		it1.first.getVertexArray().bind();
		for (auto const& it2 : it1.second)
		{
			if (!it2->isLamp())
				it2->drawShadow(shadowMatrices, it1.first.getIndexBuffer().getCount(), shader);
		}
	}
	frameBuffer.unbind();
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
