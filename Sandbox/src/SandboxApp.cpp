
#include <AmyWare.h>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include <string>

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



	ExLayer() : Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f), squarePosition(0.0f) {
		vertexArray.reset(AmyWare::VertexArray::Create());
		tracker = DataTracker();
		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<AmyWare::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(AmyWare::VertexBuffer::Create(vertices, sizeof(vertices)));

		AmyWare::BufferLayout layout = {
			{ AmyWare::ShaderDataType::Float3, "a_Position" },
			{ AmyWare::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[6] = { 0, 1, 2, 2, 1, 3 };
		std::shared_ptr<AmyWare::IndexBuffer> indexBuffer;
		indexBuffer.reset(AmyWare::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);





		// make vertex array
		squareVA.reset(AmyWare::VertexArray::Create());
		// make vertex buffer
		float vertices2[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
		};
		std::shared_ptr<AmyWare::VertexBuffer> squareVB;
		squareVB.reset(AmyWare::VertexBuffer::Create(vertices2, sizeof(vertices2)));
		// make layout
		squareVB->SetLayout({
			{ AmyWare::ShaderDataType::Float3, "a_Position" }
		});
		squareVA->AddVertexBuffer(squareVB);
		// make index buffer
		uint32_t indices2[6] = { 0, 1, 2, 2, 1, 3 };
		std::shared_ptr<AmyWare::IndexBuffer> squreIB;
		squreIB.reset(AmyWare::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		squareVA->SetIndexBuffer(squreIB);
		// make shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform *vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";



		shader.reset(new AmyWare::Shader(vertexSrc, fragmentSrc));
		shader2.reset(new AmyWare::Shader(vertexSrc2, fragmentSrc2));
	
	}
	void OnUpdate(AmyWare::Timestep ts) override {
		AmyWare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AmyWare::RenderCommand::Clear();

		
		glm::vec3 pos = camera.GetPosition();
		float spd = 5;
		if (AmyWare::Input::IsKeyDown(AW_KEY_LEFT)) pos.x -= spd * ts;
		if (AmyWare::Input::IsKeyDown(AW_KEY_RIGHT)) pos.x += spd * ts;
		if (AmyWare::Input::IsKeyDown(AW_KEY_UP)) pos.y += spd * ts;
		if (AmyWare::Input::IsKeyDown(AW_KEY_DOWN)) pos.y -= spd * ts;
		camera.SetPosition(pos);

		if (AmyWare::Input::IsKeyDown(AW_KEY_W)) squarePosition.y += spd * ts;
		if (AmyWare::Input::IsKeyDown(AW_KEY_A)) squarePosition.x -= spd * ts;
		if (AmyWare::Input::IsKeyDown(AW_KEY_S)) squarePosition.y -= spd * ts;
		if (AmyWare::Input::IsKeyDown(AW_KEY_D)) squarePosition.x += spd * ts;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), squarePosition);

		AmyWare::Renderer::BeginScene(camera);
		AmyWare::Renderer::Submit(shader2, squareVA);
		AmyWare::Renderer::Submit(shader, vertexArray, transform);
		AmyWare::Renderer::EndScene();
		tracker.Push(ts);
	}
	virtual void OnImGuiRender() override {

		ImGui::Begin("Stuff Log");
		ImGui::Text("SECONDS PER FRAME  :  %f", tracker.GetTime());
		ImGui::Text(" ----- Square Position -----");
		ImGui::Text("(%f, %f)", squarePosition.x, squarePosition.y);
		ImGui::Text(" ----- Camera Position -----");
		ImGui::Text("(%f, %f)", camera.GetPosition().x, camera.GetPosition().y);
		ImGui::End();
	}
	void OnEvent(AmyWare::Event& event) override {
	}
private:
	std::shared_ptr<AmyWare::Shader> shader;
	std::shared_ptr<AmyWare::Shader> shader2;
	std::shared_ptr<AmyWare::VertexArray> vertexArray;
	std::shared_ptr<AmyWare::VertexArray> squareVA;

	AmyWare::OrthographicCamera camera;

	glm::vec3 squarePosition;
	DataTracker tracker;
};

class Sandbox : public AmyWare::Application {
public:
	Sandbox() {
		PushLayer(new ExLayer());
	}
	~Sandbox() {

	}
};

AmyWare::Application* AmyWare::CreateApplication() {
	return new Sandbox();
}

