#include "Objects.h"

int Objects::m_placesLeft = 7;

Objects::Objects(unsigned int maxSize): m_maxSize(maxSize)
{
	m_objects = Objects::myMaps();
}

void Objects::addObject(std::pair<IndexBuffer, VertexArray> const& pair, std::shared_ptr<Object> const& object, std::string const& name,
	bool night)
{
	if (m_placesLeft <= 0)
		return;
	if (!night && object->isLight())
		return;
	auto lastMap = m_objects[object->getShader()][pair];
	if (lastMap.find(name) == lastMap.end())
	{
		m_placesLeft--;
		m_objects[object->getShader()][pair][name] = object;
	}
}

Objects::myMaps Objects::getObjects()
{
	return m_objects;
}

void Objects::draw(Matrix4f const& view, Matrix4f const& projection, bool night)
{
	if (!night)
	{
		auto it = std::find_if(m_objects.begin(), m_objects.end(), [](auto x) {return x.first.getShaderType() == Shader::ShaderType::LAMP; });
		if (it != m_objects.end())
		{
			m_placesLeft += getSizeShaderMap(it);
			m_objects.erase(it->first);
		}
	}
	for (auto it1 : m_objects)
	{
		it1.first.bind();
		for (auto const& it2 : it1.second)
		{
			it2.first.second.bind();
			it2.first.first.bind();
			for (auto const& it3 : it2.second)
			{
				it3.second->draw(view, projection, it2.first.first.getCount());
			}
		}
	}
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
