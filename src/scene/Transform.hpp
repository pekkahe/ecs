#pragma once

#include <component/IComponent.hpp>

#include <core/Defines.hpp>

namespace eng
{
	class Transform : public IComponent
	{
	public:
		vec3 position;
		qua	 rotation = qua(1.0f, 0.0f, 0.0f, 0.0f);
		vec3 scale = vec3(1.0f, 1.0f, 1.0f);

		Transform() = default;
		Transform(vec3 pos) : position(pos) {}
		Transform(vec3 pos, qua rot) : position(pos), rotation(rot) {}
	};
}