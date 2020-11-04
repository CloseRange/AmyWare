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
		template<typename T, typename Func>
		void DrawComp(Entity e, char* text, Func f);
		Ref<Scene> context;
		Entity selectionContext;
	};
}

