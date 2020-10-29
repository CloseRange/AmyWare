#pragma once

#include "AmyWare.h"
#include "ParticleSystem.h"

class Sandbox2D : public AmyWare::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;


	void OnUpdate(AmyWare::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(AmyWare::Event& e) override;

private:
	AmyWare::OrthographicCameraController camera;
	AmyWare::Ref<AmyWare::Texture2D> texture;
	AmyWare::Ref<AmyWare::Texture2D> textureMap;
	AmyWare::Ref<AmyWare::SubTexture2D> subTexTree;
	glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	AmyWare::Drawable drawQuads[20*20];

	ParticleSystem partSys;
	ParticleProps part;
};

