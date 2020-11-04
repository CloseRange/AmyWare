#pragma once

#include "AmyWare.h"
#include "AmyWare/Core/Core.h"
#include "AmyWare/Scene/Scene.h"
#include "AmyWare/Scene/Entity.h"

namespace AmyWare {
	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
		template<typename T, typename UIFunction>
		void DrawComp(const std::string& text, Entity entity, bool destroyable, UIFunction uiFunction);
		Ref<Scene> context;
		Entity selectionContext;
	};
}

