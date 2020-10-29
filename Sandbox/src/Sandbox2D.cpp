#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <chrono>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), camera(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
	AW_PROFILE_FUNCTION();

	AmyWare::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	texture = AmyWare::Texture2D::Create("assets/textures/bork.png");
	textureMap = AmyWare::Texture2D::Create("assets/textures/outside.png");
	subTexTree = AmyWare::SubTexture2D::CreateFromCoords(textureMap, { 1, 15 }, { 16, 16 });

	part.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	part.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	part.SizeBegin = 0.5f, part.SizeVariation = 0.3f, part.SizeEnd = 0.0f;
	part.LifeTime = 1.0f;
	part.Velocity = { 0.0f, 0.0f };
	part.VelocityVariation = { 3.0f, 1.0f };
	part.Position = { 0.0f, 0.0f };

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			float dx = (float)x / 20.0f;
			float dy = (float)y / 20.0f;
			float range = 10.0f;
			float s = range / 20.0f - .05; // area / count
			drawQuads[y * 20 + x] = AmyWare::Drawable()
				.SetPosition(dx * range - range/2.0f, dy * range - range/2.0f)
				.SetSize(s, s)
				.SetColorN(dx, 0.4f, dy, .5f)
				.SetDepth(-.5f)
				.Clean();
		}
	}

}

void Sandbox2D::OnDetach() {
	AW_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(AmyWare::Timestep ts) {
	AW_PROFILE_FUNCTION();


	camera.OnUpdate(ts);

	AmyWare::Renderer2D::ResetStats();
	AmyWare::Renderer2D::GetStats().Time = ts;

	AmyWare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	AmyWare::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += ts * 50.0f;
	auto d = AmyWare::Drawable().SetColor(150, 20, 50).SetPosition(-.5f, -.5f, .5f, .5f);

	AmyWare::Renderer2D::BeginScene(camera.GetCamera());
	
	//AmyWare::Renderer2D::DrawQuad(-.5f, -.5f, .5f, .5f, color);
	AmyWare::Drawable().SetTexture(subTexTree).SetDepth(.1f).Draw();
	AmyWare::Drawable().SetPosition(.6f, 0.0f).SetRotationD(rotation).SetTexture(texture).SetDepth(.1f).Draw();
	//AmyWare::Renderer2D::DrawQuad(-.7f, -.3f, .7f, .3f, glm::vec4({ 0.3f, 0.8f, 0.2f, 1.0f }));
	AmyWare::Drawable()
		.SetPosition(-.2, -.2, .2, .2)
		.SetColor(255, 100, 100, 100)
		.SetDepth(0.5f)
		.Draw();
	//AmyWare::Renderer2D::EndScene();
	//AmyWare::Renderer2D::BeginScene(camera.GetCamera());
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			//float ny = (y + 5) / 10.0f;
			//float nx = (x + 5) / 10.0f;
			//AmyWare::Drawable().SetPosition(x, y).SetSize(.45f, .45f).SetColorN(nx, 0.4f, ny, .5f).Draw();
			// drawQuads[y * 20 + x].Draw();
		}
	}
	AmyWare::Renderer2D::EndScene();

	if (AmyWare::Input::IsMouseDown(AW_MOUSE_BUTTON_LEFT)) {
		auto [x, y] = AmyWare::Input::GetMouse();
		auto width = AmyWare::Application::Get().GetWindow().GetWidth();
		auto height = AmyWare::Application::Get().GetWindow().GetHeight();

		auto bounds = camera.GetBounds();
		auto pos = camera.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		part.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 50; i++) {
			partSys.Emit(part);
		}
	}
	partSys.OnUpdate(ts);
	partSys.OnRender(camera.GetCamera());

}

void Sandbox2D::OnImGuiRender() {
	AW_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(color));
	auto stats = AmyWare::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("   Frame Time:          %.4f", stats.Time);
	ImGui::Text("   FPS:                 %.2f", (1.0f / stats.Time));
	ImGui::Text("   Quad Reset Count:    %d", stats.QuadRefreshes);
	ImGui::Text("   Draw Calls:          %d", stats.DrawCalls);
	ImGui::Text("   Quads:               %d", stats.QuadCount);
	ImGui::Text("   Vertices:            %d", stats.GetTotalVertexCount());
	ImGui::Text("   Indices:             %d", stats.GetTotalIndexCount());
	// uint32_t texID = frameBuffer->GetColorAttachmentRendererID();
	// ImGui::Image((void*) texID, ImVec2{1280, 720});
	ImGui::End();


}

void Sandbox2D::OnEvent(AmyWare::Event& e) {
	camera.OnEvent(e);

}
