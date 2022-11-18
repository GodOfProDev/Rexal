#include "rxpch.h"
#include "Entity.h"

namespace Rexal {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}