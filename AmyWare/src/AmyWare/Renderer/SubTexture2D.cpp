#include "awpch.h"
#include "SubTexture2D.h"

namespace AmyWare {
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& tex, const glm::vec2& min, const glm::vec2& max) : texture(tex) {
		texCoords[0] = { min.x, min.y };
		texCoords[1] = { max.x, min.y };
		texCoords[2] = { max.x, max.y };
		texCoords[3] = { min.x, max.y };

	}
	const void SubTexture2D::SetTexture(const Ref<Texture2D>& tex) {
		texture = tex;
	}
	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize) {
		glm::vec2 min = { ((coords.x + 0) * cellSize.x) / texture->GetWidth(), ((coords.y + 0) * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);
	}
}

