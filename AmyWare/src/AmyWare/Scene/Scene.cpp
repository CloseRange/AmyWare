#include "awpch.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <AmyWare\Scene\Components.h>
#include <AmyWare\Scene\Entity.h>
#include <AmyWare\Renderer\Renderer2D.h>
#include <AmyWare\Utility\Drawable.h>

namespace AmyWare {

	Scene::Scene() {
		//entt::entity entity = registry.create();
	}
	Scene::~Scene() {
	}
	Entity Scene::CreateEntity(const std::string& name) {
		Entity entity = { registry.create(), this };
		auto& tag = entity.Add<CTag>();
		entity.Add<CTransform>();

		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
	void Scene::DestroyEntity(Entity entity) {
		registry.destroy(entity);
	}
	void Scene::OnUpdate(Timestep ts) {

		// Update Native Scripts
		registry.view<CNativeScript>().each([=](auto entity, auto& nsc) {
			if (!nsc.Instance) {
				nsc.Instance = nsc.FInstantiate();
				nsc.Instance->entity = Entity{ entity, this };
				nsc.Instance->OnCreate();
			}
			nsc.Instance->OnUpdate(ts);
		});



		Camera* activeCamera = nullptr;
		glm::mat4 activeTransform;
		{
			auto group = registry.group<CCamera>(entt::get<CTransform>);
			for (auto e : group) {
				auto [transform, cam] = group.get<CTransform, CCamera>(e);
				if (cam.Primary) {
					activeCamera = &cam.Camera;
					activeTransform = transform.GetTransform();
					break;
				}
			}
		}
		if (activeCamera) {
			Renderer2D::BeginScene(*activeCamera, activeTransform);


			auto group = registry.group<CTransform>(entt::get<CSpriteRenderer>);
			for (auto entity : group) {
				auto [transform, sprite] = group.get<CTransform, CSpriteRenderer>(entity);
				Drawable::Quad(transform.GetTransform(), sprite.Color).Draw();
			}

			Renderer2D::EndScene();
		}
	}
	void Scene::OnViewportResize(uint32_t width, uint32_t height) {
		viewportWidth = width;
		viewportHeight = height;

		auto view = registry.view<CCamera>();
		for (auto e : view) {
			auto& camComp = view.get<CCamera>(e);
			if (!camComp.FixedAspectRatio) {
				camComp.Camera.SetViewportSize(width, height);
			}
		}
		
	}



	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component) {
		static_assert(false);
	}
	template<>
	void Scene::OnComponentAdded<CTransform>(Entity entity, CTransform& component) {

	}
	template<>
	void Scene::OnComponentAdded<CCamera>(Entity entity, CCamera& component) {
		component.Camera.SetViewportSize(viewportWidth, viewportHeight);
	}
	template<>
	void Scene::OnComponentAdded<CSpriteRenderer>(Entity entity, CSpriteRenderer& component) {

	}
	template<>
	void Scene::OnComponentAdded<CNativeScript>(Entity entity, CNativeScript& component) {

	}
	template<>
	void Scene::OnComponentAdded<CTag>(Entity entity, CTag& component) {

	}
}