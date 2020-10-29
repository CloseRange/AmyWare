#include "awpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm\ext\matrix_transform.hpp>
#include "AmyWare/Utility/Drawable.h"

namespace AmyWare {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TileFactor;
		// color, texId, maskId
	};

	struct Renderer2DData {
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVerts = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> PixelTexture;
		glm::vec4 White;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData data;


	void Renderer2D::Init() {
		AW_PROFILE_FUNCTION();

		data.White = { 1.0f, 1.0f, 1.0f, 1.0f };

		// make vertex array
		data.QuadVertexArray = VertexArray::Create();
		// make vertex buffer
		data.QuadVertexBuffer = VertexBuffer::Create(data.MaxVerts * sizeof(QuadVertex));
		// make layout
		data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TileFactor" }
		});
		data.QuadVertexArray->AddVertexBuffer(data.QuadVertexBuffer);

		data.QuadVertexBufferBase = new QuadVertex[data.MaxVerts];

		// make index buffer
		uint32_t* quadIndices = new uint32_t[data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;

		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, data.MaxIndices);
		data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		data.PixelTexture = Texture2D::Create(1, 1);
		uint32_t pixData = 0xffffffff;
		data.PixelTexture->SetData(&pixData, sizeof(uint32_t));

		int32_t samplers[data.MaxTextureSlots];
		for (int32_t i = 0; i < data.MaxTextureSlots; i++)
			samplers[i] = i;

		data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		data.TextureShader->Bind();
		data.TextureShader->SetIntArray("u_Textures", samplers, data.MaxTextureSlots);

		data.TextureSlots[0] = data.PixelTexture;

		data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

	}
	void Renderer2D::Shutdown() {
		AW_PROFILE_FUNCTION();

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		AW_PROFILE_FUNCTION();

		data.TextureShader->Bind();
		data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjection());

		data.QuadIndexCount = 0;
		data.QuadVertexBufferPtr = data.QuadVertexBufferBase;

		data.TextureSlotIndex = 1;
	}
	void Renderer2D::EndScene() {
		AW_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)data.QuadVertexBufferPtr - (uint8_t*)data.QuadVertexBufferBase;
		data.QuadVertexBuffer->SetData(data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush() {
		for (uint32_t i = 0; i < data.TextureSlotIndex; i++) {
			data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(data.QuadVertexArray, data.QuadIndexCount);
		data.Stats.DrawCalls++;
	}
	void Renderer2D::StartNewBatch() {
		EndScene();

		data.QuadIndexCount = 0;
		data.QuadVertexBufferPtr = data.QuadVertexBufferBase;

		data.TextureSlotIndex = 1;
	}

	Ref<Texture2D> Renderer2D::PixelTexture() {
		return data.PixelTexture;
	}

	void Renderer2D::DrawQuad(float x1, float y1, float x2, float y2) {
		Drawable::Quad(x1, y1, x2, y2).Draw();
	}
	void Renderer2D::DrawQuad(float x1, float y1, float x2, float y2, glm::vec4& color) {
		Drawable::Quad(x1, y1, x2, y2, color).Draw();
	}
	void Renderer2D::DrawTexture(Ref<Texture2D> texture, float x, float y) {
		Drawable::Texture(texture, x, y).Draw();
	}
	void Renderer2D::DrawTexture(Ref<Texture2D> texture, float x, float y, float scaleX, float scaleY) {
		Drawable::Texture(texture, x, y).SetSize(scaleX, scaleY).Draw();
	}
	void Renderer2D::DrawTexture(Ref<Texture2D> texture, float x, float y, float scaleX, float scaleY, glm::vec4& color) {
		Drawable::Texture(texture, x, y).SetSize(scaleX, scaleY).SetColor(color).Draw();
	}

	void Renderer2D::DrawComplex(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec2* textureCoords, const glm::vec4& color, float tileCount) {
		AW_PROFILE_FUNCTION();
		float textureIndex = GetSetTextureIndex(texture);

		//const glm::vec2* textureCoords = subtexture.GetTexCoords();//{ { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		constexpr size_t quadVertexCount = 4;
		for (size_t i = 0; i < quadVertexCount; i++) {
			data.QuadVertexBufferPtr->Position = transform * data.QuadVertexPositions[i];
			data.QuadVertexBufferPtr->Color = color;
			data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			data.QuadVertexBufferPtr->TexIndex = textureIndex;
			data.QuadVertexBufferPtr->TileFactor = tileCount;
			data.QuadVertexBufferPtr++;
		}

		data.QuadIndexCount += 6;


		data.Stats.QuadCount++;
	}
	float Renderer2D::GetSetTextureIndex(Ref<Texture2D> tex) {
		AW_PROFILE_FUNCTION();
		if (data.QuadIndexCount >= Renderer2DData::MaxIndices)
			StartNewBatch();

		float textureIndex = -1.0f;

		for (uint32_t i = 0; i < data.TextureSlotIndex; i++) {
			if (*data.TextureSlots[i].get() == *tex.get()) {
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex < 0.0f) {
			textureIndex = (float)data.TextureSlotIndex;
			data.TextureSlots[data.TextureSlotIndex] = tex;
			data.TextureSlotIndex++;
		}
		return textureIndex;
	}
	Renderer2D::Statistics& Renderer2D::GetStats() {
		return data.Stats;
	}
	void Renderer2D::ResetStats() {
		memset(&data.Stats, 0, sizeof(Statistics));
	}
}