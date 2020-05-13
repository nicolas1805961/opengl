#pragma once

#include <utility>
#include "IndexBuffer.h"
#include "VertexArray.h"

class Screen
{
public:
	Screen();
	static std::pair<VertexArray, unsigned int> initializeLayout();
	~Screen();

private:

};