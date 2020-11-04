#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "AmyWare/Scene/Components.h"
#include <glm\gtc\type_ptr.hpp>

namespace AmyWare {
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) {
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context) {
		this->context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender() {
		ImGui::Begin("Scene");

		context->registry.each([&](auto entityID) {
			Entity entity = { entityID, context.get() };
			DrawEntityNode(entity);
		});
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
			selectionContext = {};
		}

		if (ImGui::BeginPopupContextWindow(0, 1, false)) {
			if (ImGui::MenuItem("Create Empty Entity"))
				context->CreateEntity("Empty Entity");
			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (selectionContext) {
			DrawComponents(selectionContext);
			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");
			if (ImGui::BeginPopup("AddComponent")) {
				if (ImGui::MenuItem("Camera")) {
					selectionContext.Add<CCamera>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Sprite Renderer")) {
					selectionContext.Add<CSpriteRenderer>();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
	void SceneHierarchyPanel::DrawEntityNode(Entity entity) {
		auto& tag = entity.Get<CTag>().Tag;
		auto sel = (selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0;
		ImGuiTreeNodeFlags flags = sel | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked()) {
			selectionContext = entity;
		}
		bool deleted = false;
		if (ImGui::BeginPopupContextItem()) {
			if (ImGui::MenuItem("Delete Entity")) deleted = true;
			ImGui::EndPopup();
		}
		if (opened) {
			ImGui::Text("A good ol' test");
			ImGui::TreePop();
		}

		if (deleted) {
			if (selectionContext == entity) selectionContext = {};
			context->DestroyEntity(entity);
		}
	}

	static ImVec2 PushVecControl(const std::string& label, int count=3, float columnWidth = 100.0f) {
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);

		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(count, ImGui::CalcItemWidth());

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		return { lineHeight + 3.0f, lineHeight };
	}
	static void PopVecControl() {
		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}
	static void AddVecButton(float& value, char* name, char* name2, ImVec4 c1, ImVec4 c2, ImVec2 buttonSize, float resetValue = 0.0f) {
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushStyleColor(ImGuiCol_Button, c1);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, c2);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, c1);
		ImGui::PushFont(boldFont);
		if (ImGui::Button(name, buttonSize)) value = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat(name2, &value, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
	}
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f) {
		ImVec2 buttonSize = PushVecControl(label, 3, 100.0f);

		AddVecButton(values.x, "X", "##X", { 0.8f, 0.1f, 0.15f, 1.0f }, { 0.9f, 0.2f, 0.2f, 1.0f }, buttonSize, resetValue);
		ImGui::SameLine();
		AddVecButton(values.y, "Y", "##Y", { 0.2f, 0.7f, 0.2f, 1.0f }, { 0.3f, 0.8f, 0.3f, 1.0f }, buttonSize, resetValue);
		ImGui::SameLine();
		AddVecButton(values.z, "Z", "##Z", { 0.1f, 0.25f, 0.8f, 1.0f }, { 0.2f, 0.35f, 0.9f, 1.0f }, buttonSize, resetValue);

		PopVecControl();
	}
	static void DrawVecPosition2D(const std::string& label, glm::vec3& values, float resetValue = 0.0f) {
		ImVec2 buttonSize = PushVecControl(label, 2, 100.0f);

		AddVecButton(values.x, "X", "##X", { 0.8f, 0.1f, 0.15f, 1.0f }, { 0.9f, 0.2f, 0.2f, 1.0f }, buttonSize, resetValue);
		ImGui::SameLine();
		AddVecButton(values.y, "Y", "##Y", { 0.1f, 0.25f, 0.8f, 1.0f }, { 0.2f, 0.35f, 0.9f, 1.0f }, buttonSize, resetValue);

		PopVecControl();
	}
	static void DrawVecRotation2D(const std::string& label, glm::vec3& values, float resetValue = 0.0f) {
		ImVec2 buttonSize = PushVecControl(label, 2, 100.0f);

		AddVecButton(values.z, "R", "##R", { 0.25f, 0.1f, 0.8f, 1.0f }, { 0.35f, 0.2f, 0.9f, 1.0f }, buttonSize, resetValue);

		PopVecControl();
	}
	static void DrawVecScale2D(const std::string& label, glm::vec3& values, float resetValue = 1.0f) {
		ImVec2 buttonSize = PushVecControl(label, 2, 100.0f);

		AddVecButton(values.x, "W", "##W", { 0.8f, 0.1f, 0.15f, 1.0f }, { 0.9f, 0.2f, 0.2f, 1.0f }, buttonSize, resetValue);
		ImGui::SameLine();
		AddVecButton(values.y, "H", "##H", { 0.1f, 0.25f, 0.8f, 1.0f }, { 0.2f, 0.35f, 0.9f, 1.0f }, buttonSize, resetValue);

		PopVecControl();
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity) {
	if (entity.Has<CTag>()) {
		auto& tag = entity.Get<CTag>().Tag;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
			tag = std::string(buffer);
		}
	}
	DrawComp<CTransform>(entity, "Transform", [&]() {
		auto& tc = entity.Get<CTransform>();

		const char* strs[] = { "0D", "1D", "2D", "3D" };
		const char* viewPersp = strs[(int)tc.ViewPerspective];
		if (ImGui::BeginCombo("Perspective", viewPersp)) {
			bool sel2 = tc.ViewPerspective == Perspective::TWO;
			bool sel3 = tc.ViewPerspective == Perspective::THREE;
			if (ImGui::Selectable("2D", sel2))
				tc.ViewPerspective = Perspective::TWO;
			if (ImGui::Selectable("3D", sel3))
				tc.ViewPerspective = Perspective::THREE;
			if (sel2 || sel3) {
				ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		switch (tc.ViewPerspective) {
		case Perspective::TWO:
		{
			DrawVecPosition2D("Position", tc.Position);
			DrawVecScale2D("Scale", tc.Scale, 1.0f);
			DrawVecRotation2D("Rotation", tc.Rotation);
			break;
		}
		case Perspective::THREE:
		{
			DrawVec3Control("Position", tc.Position);
			DrawVec3Control("Rotation", tc.Rotation);
			DrawVec3Control("Scale", tc.Scale, 1.0f);
			break;
		}
		}
	});
	DrawComp<CCamera>(entity, "Camera", [&]() {
		auto& cameraComp = entity.Get<CCamera>();
		auto& camera = cameraComp.Camera;

		ImGui::Checkbox("Primary", &cameraComp.Primary);

		const char* projectionStrings[] = { "Perspective", "Orthographic" };
		const char* cProjectionString = projectionStrings[(int)camera.GetProjectionType()];
		if (ImGui::BeginCombo("Projection", cProjectionString)) {
			for (int i = 0; i < 2; i++) {
				bool sel = cProjectionString == projectionStrings[i];
				if (ImGui::Selectable(projectionStrings[i], sel)) {
					cProjectionString = projectionStrings[i];
					camera.SetProjectionType((SceneCamera::ProjectionType) i);
				}
				if (sel) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
			float oSize = glm::degrees(camera.GetPerspectiveFOV());
			if (ImGui::DragFloat("Vertical FOV", &oSize)) camera.SetPerspectiveFOV(glm::radians(oSize));
			float oNear = camera.GetPerspectiveNearClip();
			if (ImGui::DragFloat("Near Clip", &oNear)) camera.SetPerspectiveNearClip(oNear);
			float oFar = camera.GetPerspectiveFarClip();
			if (ImGui::DragFloat("Far Clip", &oFar)) camera.SetPerspectiveFarClip(oFar);
		} else {
			float oSize = camera.GetOrthographicSize();
			if (ImGui::DragFloat("Size", &oSize)) camera.SetOrthographicSize(oSize);
			float oNear = camera.GetOrthographicNearClip();
			if (ImGui::DragFloat("Near Clip", &oNear)) camera.SetOrthographicNearClip(oNear);
			float oFar = camera.GetOrthographicFarClip();
			if (ImGui::DragFloat("Far Clip", &oFar)) camera.SetOrthographicFarClip(oFar);

			ImGui::Checkbox("Fixed Aspect Ratio", &cameraComp.FixedAspectRatio);
		}
	});
	DrawComp<CSpriteRenderer>(entity, "Sprite Renderer", [&]() {
		auto& src = entity.Get<CSpriteRenderer>();
		ImGui::ColorEdit4("Color", glm::value_ptr(src.Color));
	});
}



	template<typename T, typename Func>
	void SceneHierarchyPanel::DrawComp(Entity entity, char* text, Func f) {
		if (!entity.Has<T>()) return;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap, text);

		ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
		if (ImGui::Button("+", ImVec2{ 20, 20 })) {
			ImGui::OpenPopup("ComponentSettings");
		}
		ImGui::PopStyleVar();
		bool removeComponent = false;
		if (ImGui::BeginPopup("ComponentSettings")) {
			if (ImGui::MenuItem("Remove Component"))
				removeComponent = true;
			ImGui::EndPopup();
		}
		
		
		if (open) {
			f();
			ImGui::TreePop();
		}

		if (removeComponent)
			entity.Remove<T>();
	}
}
