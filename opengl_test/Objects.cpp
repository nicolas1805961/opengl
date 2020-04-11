#include "Objects.h"

Objects::Objects(unsigned int maxSize): m_maxSize(maxSize)
{
	m_objects = std::map<Shader, std::map<std::pair<IndexBuffer, VertexArray>, std::vector<std::shared_ptr<Object>>, comparePair>>();
}

void Objects::addObject(std::pair<IndexBuffer, VertexArray> const& pair, std::shared_ptr<Object> const& object)
{
	static unsigned int callNumber = 0;
	callNumber++;
	if (callNumber > m_maxSize)
		return;
	m_objects[object->getShader()][pair].push_back(object);
}

std::map<Shader, std::map<std::pair<IndexBuffer, VertexArray>, std::vector<std::shared_ptr<Object>>, comparePair>> Objects::getObjects()
{
	return m_objects;
}

void Objects::draw(Matrix4f const& view, Matrix4f const& projection) const
{
	for (auto it1 : m_objects)
	{
		it1.first.bind();
		for (auto const& it2 : it1.second)
		{
			it2.first.second.bind();
			it2.first.first.bind();
			for (auto const& it3 : it2.second)
			{
				it3->draw(view, projection, it2.first.first.getCount());
			}
		}
	}
}

void Objects::draw(Matrix4f const& view, Matrix4f const& projection)
{
	for (auto it1 : m_objects)
	{
		it1.first.bind();
		for (auto const& it2 : it1.second)
		{
			it2.first.second.bind();
			it2.first.first.bind();
			for (auto const& it3 : it2.second)
			{
				it3->draw(view, projection, it2.first.first.getCount());
			}
		}
	}
}

void Objects::clear()
{
	m_objects.clear();
}

bool Objects::trace(Ray& ray)
{
	for (auto const& it1 : m_objects)
	{
		for (auto const& it2 : it1.second)
		{
			for (auto const& it3 : it2.second)
			{
				if (it3->intersectRay(ray))
				{
					if (ray.get_t_distance() < ray.get_nearest())
					{
						ray.set_nearest(ray.get_t_distance());
						ray.set_hit(it3);
					}
				}
			}
		}
	}
	ray.set_t_distance(ray.get_nearest());
	return (ray.get_hit() != nullptr);
}
