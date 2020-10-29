
#include <AmyWare.h>
#include <AmyWare/Core/EntryPoint.h>

#include "imgui/imgui.h"
#include "EditorLayer.h"

namespace AmyWare {
	class AmyEditor : public Application {
	public:
		AmyEditor() : Application("AmyEdit") {
			PushLayer(new EditorLayer());
		}
		~AmyEditor() {

		}
	};

	Application* CreateApplication() {
		return new AmyEditor();
	}

}