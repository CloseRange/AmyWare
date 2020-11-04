#pragma once
#include <glm\glm.hpp>
#include <glm\ext\matrix_transform.hpp>
#include "SceneCamera.h"
#include <AmyWare\Scene\ScriptableEntity.h>
#include <AmyWare\Renderer\Perspective.h>

namespace AmyWare {
	struct CTag {
		std::string Tag;

		CTag() = default;
		CTag(const CTag&) = default;
		CTag(const std::string& tag) : Tag(tag) {}
	};
	struct CTransform {
		Perspective ViewPerspective = Perspective::TWO;

		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotation{ 0.0f };
		glm::vec3 Scale{ 1.0f };

		CTransform() = default;
		CTransform(const CTransform&) = default;
		CTransform(const glm::vec3& position) : Position(position) {};

		glm::mat4 GetTransform() const {
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
				* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
				* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });

			return glm::translate(glm::mat4(1.0f), Position)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};
	struct CSpriteRenderer {
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		CSpriteRenderer() = default;
		CSpriteRenderer(const CSpriteRenderer&) = default;
		CSpriteRenderer(const glm::vec4& color) : Color(color) {};
	};
	struct CCamera {
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CCamera() = default;
		CCamera(const CCamera&) = default;
	};
	struct CNativeScript {
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*FInstantiate)();
		void(*FDestroy)(CNativeScript*);

		template<typename T>
		void Bind() {
			FInstantiate = []() { return static_cast<ScriptableEntity*>(new T()); };
			FDestroy = [](CNativeScript* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}

