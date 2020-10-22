#include "awpch.h"
#include "Renderer.h"

namespace AmyWare {

	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera) {
		sceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}
	void Renderer::EndScene() {
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}