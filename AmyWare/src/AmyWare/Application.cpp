#include "awpch.h"
#include "Application.h"

#include "AmyWare/Renderer/Renderer.h"

#include "AmyWare/Log.h"
#include "Input.h"



namespace AmyWare {
#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;


	Application::Application() {
		AW_CORE_ASSERT(!Instance, "Application already defined")
		Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		// Palette::ApplyToGui(Palette::AmyPalette);




		vertexArray.reset(VertexArray::Create());

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[6] = { 0, 1, 2, 2, 1, 3 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);





		// make vertex array
		squareVA.reset(VertexArray::Create());
		// make vertex buffer
		float vertices2[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(vertices2, sizeof(vertices2)));
		// make layout
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		squareVA->AddVertexBuffer(squareVB);
		// make index buffer
		uint32_t indices2[6] = { 0, 1, 2, 2, 1, 3 };
		std::shared_ptr<IndexBuffer> squreIB;
		squreIB.reset(IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		squareVA->SetIndexBuffer(squreIB);
		// make shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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



		shader.reset(new Shader(vertexSrc, fragmentSrc));
		shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
	}
	Application::~Application() {

	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClosed));


		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			auto l = (*--it);
			l->OnEvent(e);
			if (e.Handled) break;
		}
	}
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::Run() {

		while (m_Running) {
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();
			//shader2->Bind();
			//Renderer::Submit(squareVA);
			shader->Bind();
			Renderer::Submit(vertexArray);
			Renderer::EndScene();



			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}
	bool Application::OnWindowClosed(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}
}