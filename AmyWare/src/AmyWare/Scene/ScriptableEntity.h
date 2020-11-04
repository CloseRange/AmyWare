#pragma once

#include "Entity.h"

namespace AmyWare {
	class ScriptableEntity {
	public:
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent() {
			return entity.Get<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}

	private:
		Entity entity;
		friend class Scene;
	};
}
