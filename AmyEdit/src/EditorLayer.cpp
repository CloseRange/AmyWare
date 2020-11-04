#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace AmyWare {
	EditorLayer::EditorLayer() : Layer("EditorLayer"), camera(1280.0f / 720.0f) {
	}

	void EditorLayer::OnAttach() {
		AW_PROFILE_FUNCTION();

		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		frameBuffer = FrameBuffer::Create(fbSpec);

		// texture = Texture2D::Create("assets/textures/bork.png");
		// textureMap = Texture2D::Create("assets/textures/outside.png");
		// subTexTree = SubTexture2D::CreateFromCoords(textureMap, { 1, 15 }, { 16, 16 });

		activeScene = CreateRef<Scene>();
		square = activeScene->CreateEntity("Square");
		square.Add<CSpriteRenderer>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		square = activeScene->CreateEntity("Square 2");
		square.Add<CSpriteRenderer>(glm::vec4{ 0.0f, 1.0f, 1.0f, 1.0f });

		cameraEntity = activeScene->CreateEntity("Camera");
		cameraEntity.Add<CCamera>();
		
		cameraEntity2 = activeScene->CreateEntity("Camera 2");
		cameraEntity2.Add<CCamera>();



		class CameraController : public ScriptableEntity {
		public:
			void OnCreate() {

			}
			void OnDestroy() {

			}
			void OnUpdate(Timestep ts) {
				auto& prime = GetComponent<CCamera>().Primary;
				if (!prime) return;
				auto& transform = GetComponent<CTransform>().Position;
				float spd = 5.0f;
				if (Input::IsKeyDown(KeyCode::A))
					transform.x -= spd * ts;
				if (Input::IsKeyDown(KeyCode::D))
					transform.x += spd * ts;
				if (Input::IsKeyDown(KeyCode::W))
					transform.y += spd * ts;
				if (Input::IsKeyDown(KeyCode::S))
					transform.y -= spd * ts;
			}
		};
		cameraEntity.Add<CNativeScript>().Bind<CameraController>();
		cameraEntity2.Add<CNativeScript>().Bind<CameraController>();

		scenePanel.SetContext(activeScene);

	}

	void EditorLayer::OnDetach() {
		AW_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(Timestep ts) {
		AW_PROFILE_FUNCTION();
		FrameBufferSpecification spec = frameBuffer->GetSpecification();

		if(FrameBufferSpecification spec = frameBuffer->GetSpecification();
			viewportSize.x > 0.0f && viewportSize.y > 0.0f && 
			(spec.Width != viewportSize.x || spec.Height != viewportSize.y)) {


			frameBuffer->Resize((uint32_t) viewportSize.x, (uint32_t) viewportSize.y);
			camera.Resize(viewportSize.x, viewportSize.y);

			activeScene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		}


		if(viewportFocused) camera.OnUpdate(ts);


		Renderer2D::ResetStats();
		Renderer2D::GetStats().Time = ts;

		// ----------   RENDER PREP   ---------------
		frameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();


		// -----------   UPDATE SCENE   --------------
		activeScene->OnUpdate(ts);

		frameBuffer->Unbind();

	}

	void EditorLayer::OnImGuiRender() {
		AW_PROFILE_FUNCTION();

		// for (auto& r : profileResults) {
		// 	char label[50];
		// 	strcpy(label, "%.3fms  ");
		// 	strcat(label, r.Name);
		// 	ImGui::Text(label, r.Time);
		// }
		// profileResults.clear();

		static bool dockspaceOpen = true;

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		} else {
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				// ImGui::Separator();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}


		ImGui::Begin("Renderer Stats");
		ImGui::Separator();


		scenePanel.OnImGuiRender();

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Frame Time:          %.4f", stats.Time);
		ImGui::Text("FPS:                 %.2f", (1.0f / stats.Time));
		ImGui::Text("Quad Reset Count:    %d", stats.QuadRefreshes);
		ImGui::Text("Draw Calls:          %d", stats.DrawCalls);
		ImGui::Text("Quads:               %d", stats.QuadCount);
		ImGui::Text("Vertices:            %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices:             %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		viewportFocused = ImGui::IsWindowFocused();
		viewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewportFocused || !viewportHovered);
		
		ImVec2 vs = ImGui::GetContentRegionAvail();
		if (viewportSize != *((glm::vec2*)&vs) && vs.x > 0 && vs.y > 0) {
			//frameBuffer->Resize((uint32_t)vs.x, (uint32_t)vs.y);
			viewportSize = { vs.x, vs.y };
			//camera.Resize(viewportSize.x, viewportSize.y);
		}
		uint32_t texID = frameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)texID, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e) {
		camera.OnEvent(e);

	}
}
