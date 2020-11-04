#pragma once
#include "Scene.h"
#include <yaml-cpp/yaml.h>
#include "Entity.h"

namespace AmyWare {
	class SceneSerializer {
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);

		template<typename T, typename Callback>
		void PushComp(const char* name, Callback callback);

		template<typename T>
		void PushProp(const char* name, T value);

		void SerializeEntity(Entity entity);

	private:
		Ref<Scene> sceneContext;
		YAML::Emitter out;
		Entity currentEntity;

	};
}


