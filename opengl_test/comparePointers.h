#pragma once

#include "Shader.h"
#include <memory>
#include "Object.h"

class comparePointers
{
public:
	bool operator()(std::shared_ptr<Object> const& left, std::shared_ptr<Object> const& right) const
	{
		return left->getTranslation() < right->getTranslation();
	}
};