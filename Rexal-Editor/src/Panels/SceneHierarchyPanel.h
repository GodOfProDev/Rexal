#pragma once

#include "Rexal/Scene/Scene.h"
#include "Rexal/Core/Log.h"
#include "Rexal/Core/Base.h"
#include "Rexal/Scene/Entity.h"

namespace Rexal {

	class SceneHierarchyPanel 
	{
	public:
		SceneHierarchyPanel() {}
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}