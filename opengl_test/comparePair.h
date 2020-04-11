#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"

class comparePair
{
public:
	bool operator()(std::pair<IndexBuffer, VertexArray> const& left, std::pair<IndexBuffer, VertexArray> const& right) const
	{
		//return ((left.first < right.first) || (left.second < right.second));
		return left.first < right.first || (!(right.first < left.first) && left.second < right.second);
	}
};
