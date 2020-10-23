#pragma once

#include "AmyWare/Renderer/Texture.h"

namespace AmyWare {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return width; }
		virtual uint32_t GetHeight() const override { return height; };
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t width, height;
		uint32_t rendererID;
		std::string path;
	};
}

