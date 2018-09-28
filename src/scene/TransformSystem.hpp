#pragma once

#include <component/System.hpp>

#include <scene/Transform.hpp>

namespace eng
{
	class TransformSystem : public System
	{
	public:
		TransformSystem(Database& db);
		~TransformSystem();

		virtual void update() override;

	private:
		TableRef<Transform> m_transforms;
	};
}