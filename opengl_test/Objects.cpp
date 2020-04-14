#include "Objects.h"

int Objects::m_placesLeft = 7;

Objects::Objects()
{
	m_objects = Objects::myMaps();
}

void Objects::addObject(Shader const& shader, std::pair<IndexBuffer, VertexArray> const& pair, std::shared_ptr<Object> const& object, std::string const& name,
	bool night)
{
	if (m_placesLeft <= 0)
		return;
	if (!night && object->isLight())
		return;
	auto lastMap = m_objects[shader][pair];
	if (lastMap.find(name) == lastMap.end())
	{
		m_placesLeft--;
		m_objects[shader][pair][name] = object;
	}
}

Objects::myMaps Objects::getObjects()
{
	return m_objects;
}

void Objects::drawDay(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowViewProjMatrices,
	Shader const& lightingShader, Shader const& shadowShader, FrameBuffer const& frameBuffer)
{
	frameBuffer.bind();
	draw(shadowViewProjMatrices, shadowShader, frameBuffer.getId());
	frameBuffer.unbind();
	frameBuffer.bindTexture();
	draw(viewProjMatrices, lightingShader, 0);
	frameBuffer.unbindTexture();
}

void Objects::drawNight(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& lightingShader, Shader const& lampShader)
{
	draw(viewProjMatrices, lightingShader, 0);
	draw(viewProjMatrices, lampShader, 0);
}

void Objects::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader, unsigned int frameBufferId)
{
	myMaps::iterator it;
	if (shader.getShaderType() == Shader::ShaderType::DEPTH || shader.getShaderType() == Shader::ShaderType::LIGHTING)
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
				it2.second->draw(viewProjMatrices, it1.first.first.getCount(), shader, frameBufferId);
			}
		}
	}
	else
		std::cout << "ERROR\n";
}

void Objects::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, Shader const& shader, unsigned int frameBufferId) const
{
	if (frameBufferId == 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_DEPTH_BUFFER_BIT);
	myMaps::const_iterator it;
	if (shader.getShaderType() == Shader::ShaderType::DEPTH || shader.getShaderType() == Shader::ShaderType::LIGHTING)
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
				it2.second->draw(viewProjMatrices, it1.first.first.getCount(), shader, frameBufferId);
			}
		}
	}
	else
		std::cout << "ERROR\n";
}

void Objects::clear()
{
	m_objects.clear();
}

unsigned int Objects::getSize()
{
	unsigned int size = 0;
	for (auto it1 : m_objects)
	{
		for (auto const& it2 : it1.second)
		{
			for (auto const& it3 : it2.second)
			{
				size++;
			}
		}
	}
	return size;
}

unsigned int Objects::getSize() const
{
	unsigned int size = 0;
	for (auto it1 : m_objects)
	{
		for (auto const& it2 : it1.second)
		{
			for (auto const& it3 : it2.second)
			{
				size++;
			}
		}
	}
	return size;
}

unsigned int Objects::getSizeShaderMap(myMaps::iterator const& it)
{
	unsigned int size = 0;
	for (auto const& it2: it->second)
	{
		for (auto const& it3: it2.second)
		{
			size++;
		}
	}
	return size;
}

bool Objects::trace(Ray& ray)
{
	for (auto const& it1 : m_objects)
	{
		for (auto const& it2 : it1.second)
		{
			for (auto const& it3 : it2.second)
			{
				if (it3.second->intersectRay(ray))
				{
					if (ray.get_t_distance() < ray.get_nearest())
					{
						ray.set_nearest(ray.get_t_distance());
						ray.set_hit(it3.second);
					}
				}
			}
		}
	}
	ray.set_t_distance(ray.get_nearest());
	return (ray.get_hit() != nullptr);
}
