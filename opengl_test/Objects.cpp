#include "Objects.h"

Objects::Objects(unsigned int maxSize): m_maxSize(maxSize)
{
	m_objects = std::map<std::string, std::shared_ptr<Object>>();
}

void Objects::addObject(std::string const& name, std::shared_ptr<Object> const& object)
{
	if (m_objects.size() >= m_maxSize)
		return;
	m_objects[name] = object;
}

std::map<std::string, std::shared_ptr<Object>> Objects::getObjects()
{
	return m_objects;
}
