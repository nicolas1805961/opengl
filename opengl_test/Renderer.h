#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

class Renderer
{
public:
	Renderer();
	void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
	void clear() const;
private:
};