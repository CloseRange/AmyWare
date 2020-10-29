
#include <AmyWare.h>
#include <AmyWare/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExLayer : public AmyWare::Layer {
public:
	struct DataTracker {
	public:
		void Push(AmyWare::Timestep ts) {
			times += ts;
			if (++delta % delay == 0) {
				averageTime = times / (float)delay;
				times = 0.0f;
			}
		}
		float GetTime() { return averageTime; }
	private:
		const static signed short int delay = 10;
		float times;
		float averageTime = 0.0f;
		signed short int delta = 0;
	};



	ExLayer() : Layer("Example"), camera(1280.0f / 720.0f) {
		tracker = DataTracker();
		// make vertex array
		squareVA = AmyWare::VertexArray::Create();
		// make vertex buffer
		float vertices2[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};
		AmyWare::Ref<AmyWare::VertexBuffer> squareVB;
		squareVB = AmyWare::VertexBuffer::Create(vertices2, sizeof(vertices2));
		// make layout
		squareVB->SetLayout({
			{ AmyWare::ShaderDataType::Float3, "a_Position" },
			{ AmyWare::ShaderDataType::Float2, "a_TexCoord" }
		});
		squareVA->AddVertexBuffer(squareVB);
		// make index buffer
		uint32_t indices2[6] = { 0, 1, 2, 2, 1, 3 };
		AmyWare::Ref<AmyWare::IndexBuffer> squreIB;
		squreIB = AmyWare::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t));
		squareVA->SetIndexBuffer(squreIB);


		auto flatShader = sLibrary.Load("assets/shaders/FlatShader.glsl");
		auto textureShader = sLibrary.Load("assets/shaders/Texture.glsl");
		//shader2 = AmyWare::Shader::Create("assets/shaders/FlatShader.glsl");
	
		texture = AmyWare::Texture2D::Create("assets/textures/Icon_Key_Crystal.png");
		std::dynamic_pointer_cast<AmyWare::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<AmyWare::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);


	}
	void OnUpdate(AmyWare::Timestep ts) override {

		camera.OnUpdate(ts);
		AmyWare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AmyWare::RenderCommand::Clear();


		AmyWare::Renderer::BeginScene(camera.GetCamera());


		// AmyWare::MaterialRef material = new AmyWare::Material(shader2);

		auto flatShader = sLibrary.Get("FlatShader");
		auto textureShader = sLibrary.Get("Texture");
		std::dynamic_pointer_cast<AmyWare::OpenGLShader>(flatShader)->Bind();
		std::dynamic_pointer_cast<AmyWare::OpenGLShader>(flatShader)->UploadUniformFloat3("u_Color", color);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < squareC; y++) {
			for (int x = 0; x < squareC; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				AmyWare::Renderer::Submit(flatShader, squareVA, transform);

			}
		}
		texture->Bind();
		AmyWare::Renderer::Submit(textureShader, squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), squarePosition);
		// AmyWare::Renderer::Submit(shader, vertexArray, transform);
		AmyWare::Renderer::EndScene();
		tracker.Push(ts);
	}
	virtual void OnImGuiRender() override {

		ImGui::Begin("Debug Log");
			ImGui::Text("SECONDS PER FRAME     %f", tracker.GetTime());
			ImGui::Text("FPS                   %f", 1.0f / tracker.GetTime());
			ImGui::Text("SQUARES               %i", squareC * squareC);
		ImGui::End();
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(color));
		ImGui::End();

	}
	void OnEvent(AmyWare::Event& event) override {
		camera.OnEvent(event);
		/*
		if (event.GetEventType() == AmyWare::EventType::WindowResize) {
			auto& re = (AmyWare::WindowResizeEvent&)event;
			float zoom = (float)re.GetWidth() / 1280.0f;
			camera.SetZoomLevel(zoom);
		}
		*/
	}
private:
	AmyWare::ShaderLibrary sLibrary;

	AmyWare::Ref<AmyWare::Texture2D> texture;
	AmyWare::Ref<AmyWare::VertexArray> vertexArray;
	AmyWare::Ref<AmyWare::VertexArray> squareVA;


	DataTracker tracker;
	glm::vec3 color = { 0.2f, 0.3f, 0.8f };
	int squareC = 5;

	AmyWare::OrthographicCameraController camera;
};

class Sandbox : public AmyWare::Application {
public:
	Sandbox() {
		//PushLayer(new ExLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {

	}
};

AmyWare::Application* AmyWare::CreateApplication() {
	return new Sandbox();
}

