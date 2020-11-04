#pragma once

#include "OrthographicCamera.h"
#include <AmyWare\Renderer\Texture.h>
#include <AmyWare\Renderer\SubTexture2D.h>
#include <AmyWare\Renderer\Camera.h>

namespace AmyWare {
	class Renderer2D {
	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void EndScene();
		static void Flush();


		// Primitives
		static Ref<Texture2D> PixelTexture();

		static void DrawQuad(float x1, float y1, float x2, float y2);
		static void DrawQuad(float x1, float y1, float x2, float y2, glm::vec4& color);
		static void DrawTexture(Ref<Texture2D> texture, float x, float y);
		static void DrawTexture(Ref<Texture2D> texture, float x, float y, float scaleX, float scaleY);
		static void DrawTexture(Ref<Texture2D> texture, float x, float y, float scaleX, float scaleY, glm::vec4& color);

		static void DrawComplex(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec2* textureCoords, const glm::vec4& color, float tileCount);

		// Stats
		struct Statistics {
			uint32_t DrawableCalls = 0;
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			float Time = 0;
			uint32_t QuadRefreshes = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static Statistics& GetStats();
		static void ResetStats();
	private:
		static float GetSetTextureIndex(Ref<Texture2D> tex);
		static void StartBatch();
		static void NextBatch();
	};
}

