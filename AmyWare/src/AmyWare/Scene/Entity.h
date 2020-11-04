#pragma once

#include <entt.hpp>
#include "Scene.h"

namespace AmyWare {
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		~Entity();

		template<typename T>
		bool Has() {
			return scene->registry.has<T>(handle);
		}
		template<typename T, typename... Args>
		T& Add(Args&&... args) {
			AW_CORE_ASSERT(!Has<T>(), "Entity already has component!");
			T& component = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
			scene->OnComponentAdded<T>(*this, component);
			return component;
		}
		template<typename T>
		T& Get() {
			AW_CORE_ASSERT(Has<T>(), "Entity doesn't have component!");
			return scene->registry.get<T>(handle);
		}
		template<typename T>
		void Remove() {
			AW_CORE_ASSERT(Has<T>(), "Entity doesn't have component!");
			scene->registry.remove<T>(handle);
		}

		operator bool() const { return handle != entt::null; }
		operator entt::entity() const { return handle; }
		operator uint32_t() const { return (uint32_t)handle; }

		bool operator==(const Entity& other) const { return handle == other.handle && scene == other.scene; }
		bool operator!=(const Entity& other) const { return !(*this == other); }

	private:
		entt::entity handle{ entt::null };
		Scene* scene;
	};

}

