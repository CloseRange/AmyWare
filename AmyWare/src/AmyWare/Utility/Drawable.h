#pragma once
#include "awpch.h"
#include "AmyWare/Renderer/Texture.h"
#include "AmyWare/Renderer/SubTexture2D.h"
#include "AmyWare/Renderer/Renderer2D.h"

#include <glm/glm.hpp>
#include <glm\ext\matrix_transform.hpp>

namespace AmyWare {
	struct Drawable {
		static void Init() {
		}


		void Draw() {
			// Renderer2D::ComplexDrawRotated(Position, Size, Image, Position.z, Color, TileCount, Rotation);
			Clean();
			Renderer2D::DrawComplex(Transform, Image, TexCoords, Color, TileCount);
		}
		static Drawable Texture(Ref<Texture2D> tex, float x, float y) {
			return Drawable().SetTexture(tex).SetPosition(x, y);
		}
		static Drawable Quad(float x1, float y1, float x2, float y2) {
			return Quad(x1, y1, x2, y2, { 1.0f, 1.0f, 1.0f, 1.0f });
		}
		static Drawable Quad(float x1, float y1, float x2, float y2, glm::vec4 colorNormal) {
			return Drawable().SetPosition(x1, y1, x2, y2).SetColorN(colorNormal);
		}


		Drawable SetPosition(float x1, float y1, float x2, float y2) {
			Size = { x2 - x1, y2 - y1, 1.0f };
			Position = glm::vec3({ x1, y1, 0.0f }) + Size / glm::vec3({ 2.0f, 2.0f, 1.0f });
			Dirty = true;
			return *this;
		}
		Drawable SetPosition(float x, float y) { return SetPosition({ x, y }); }
		Drawable SetPosition(const glm::vec2& pos) {
			Position.x = pos.x;
			Position.y = pos.y;
			Dirty = true;
			return *this;
		}
		Drawable SetSize(float w, float h) { return SetSize({ w, h }); }
		Drawable SetSize(const glm::vec2& size) {
			Size.x = size.x;
			Size.y = size.y;
			Dirty = true;
			return *this;
		}
		Drawable SetColor(int r, int g, int b, int a = 255) { return SetColor({ (float)r, (float)g, (float)b, (float)a }); }
		Drawable SetColorN(float r, float g, float b, float a = 1.0f) { return SetColorN({ r, g, b, a }); }
		Drawable SetColor(const glm::vec4& color) { return SetColorN(color / 255.0f); }
		Drawable SetColorN(const glm::vec4& color) {
			Color.r = color.r;
			Color.g = color.g;
			Color.b = color.b;
			Color.a = color.a;
			return *this;
		}
		Drawable SetDepth(float d) {
			Position.z = d;
			Dirty = true;
			return *this;
		}
		Drawable SetTileCount(float tc) {
			TileCount = tc;
			return *this;
		}
		Drawable SetRotationD(float d) { return SetRotation(glm::radians(d)); }
		Drawable SetRotation(float r) {
			Rotation = r;
			Dirty = true;
			return *this;
		}
		Drawable SetTexture(const Ref<Texture2D> tex) {
			Image = tex;
			return *this;
		}
		Drawable SetTexture(const Ref<SubTexture2D> tex) {
			SetTexture(tex->GetTexture());
			SetTexCoords(tex->GetTexCoords());
			return *this;
		}
		Drawable SetTexCoords(const glm::vec2 tc[4]) {
			TexCoords[0] = tc[0];
			TexCoords[1] = tc[1];
			TexCoords[2] = tc[2];
			TexCoords[3] = tc[3];
			return *this;
		}



		Drawable Clean() {
			if (!Dirty) return *this;
			Transform = glm::translate(glm::mat4(1.0f), Position);
			if (Rotation != 0)
				Transform *= glm::rotate(glm::mat4(1.0f), Rotation, { 0.0f, 0.0f, 1.0f });
			Transform *= glm::scale(glm::mat4(1.0f), Size);
			Renderer2D::GetStats().QuadRefreshes++;
			Dirty = false;
			return *this;
		}


		glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Size{ 1.0f, 1.0f, 1.0f };
		float Rotation = 0.0f;
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Image = Renderer2D::PixelTexture();//, { 0.0f, 0.0f }, { 1.0f, 1.0f }); // Renderer2D::PixelTexture(), { 0.0f, 0.0f }, { 1.0f, 1.0f });
		glm::vec2 TexCoords[4] = { { 0.0f, 0.0f }, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
		float TileCount = 1.0f;
		glm::mat4 Transform;

	private:
		bool Dirty = false;

	};
}

