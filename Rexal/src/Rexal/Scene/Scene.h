#pragma once

#include "entt.hpp"

#include "Rexal/Core/Timestep.h"

namespace Rexal {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& GetRegistry() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}