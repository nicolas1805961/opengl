#include "VertexBufferElement.h"

VertexBufferElement::VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
	: m_type(type), m_count(count), m_normalized(normalized)
{

}

unsigned int VertexBufferElement::get_count() const
{
	return m_count;
}

unsigned int VertexBufferElement::get_type() const
{
	return m_type;
}

unsigned char VertexBufferElement::get_normalized() const
{
	return m_normalized;
}

