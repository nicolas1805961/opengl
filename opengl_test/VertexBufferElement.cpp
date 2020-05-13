#include "VertexBufferElement.h"

VertexBufferElement::VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
	: m_type(type), m_count(count), m_normalized(normalized)
{

}

/*GLuint VertexBufferElement::get_size_of_type(unsigned int type)
{
	switch (type)
	{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
	}
	return 0;
}*/

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

