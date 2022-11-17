#pragma once

#include "entt.hpp"

namespace Rexal {

	class Scene
	{
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;
	};
}