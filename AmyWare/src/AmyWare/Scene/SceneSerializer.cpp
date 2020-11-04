#include "awpch.h"
#include "SceneSerializer.h"

#include "Components.h"

#include <fstream>
#include <fstream>

#include <yaml-cpp/yaml.h>

namespace YAML {

	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs){
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}

namespace AmyWare {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : sceneContext(scene) {
	}
	template<typename T, typename Callback>
	void SceneSerializer::PushComp(const char* name, Callback callback) {
		if (currentEntity.Has<T>()) {
			out << YAML::Key << name;
			out << YAML::BeginMap;
			auto& component = currentEntity.Get<T>();
			callback(component);
			out << YAML::EndMap;
		}
	}
	template<typename T>
	void SceneSerializer::PushProp(const char* name, T value) {
		out << YAML::Key << name << YAML::Value << value;
	}

	void SceneSerializer::SerializeEntity(Entity entity) {
		out << YAML::BeginMap;
		out << YAML::Key << "Entity ID" << YAML::Value << "12837192831273";

		currentEntity = entity;

		PushComp<CTag>("Tag", [&](auto& component) {
			PushProp("Tag", component.Tag);
		});
		PushComp<CTransform>("Transform", [&](auto& component) {
			PushProp("Position", component.Position);
			PushProp("Rotation", component.Rotation);
			PushProp("Scale", component.Scale);
		});
		PushComp<CCamera>("Camera", [&](auto& component) {
			auto& cam = component.Camera;
			out << YAML::Key << "Camera Properties" << YAML::Value;
			out << YAML::BeginMap;
			PushProp("Projection Type", (int)cam.GetProjectionType());
			PushProp("Perspective FOV",      cam.GetPerspectiveFOV());
			PushProp("Perspective Near",     cam.GetPerspectiveNearClip());
			PushProp("Perspective Far",      cam.GetPerspectiveFarClip());
			PushProp("Orthographic Size",    cam.GetOrthographicSize());
			PushProp("Orthographic Near",    cam.GetOrthographicNearClip());
			PushProp("Orthographic Far",     cam.GetOrthographicFarClip());
			out << YAML::EndMap;

			PushProp("Primary", component.Primary);
			PushProp("Fixed Aspect Ratio", component.FixedAspectRatio);
		});
		PushComp<CSpriteRenderer>("Sprite Renderer", [&](auto& component) {
			PushProp("Color", component.Color);
		});

		out << YAML::EndMap;
	}
	static int MakeDir(const std::string& path, const char dilim) {
		const size_t last_slash_idx = path.rfind(dilim);
		if (std::string::npos != last_slash_idx) {
			std::string directory = path.substr(0, last_slash_idx);
			return mkdir(directory.c_str());
		}
		return -1;
	}
	void SceneSerializer::Serialize(const std::string& filepath) {
		out << YAML::Comment("AmyWare Scene File");
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "SCENE_NAME";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		sceneContext->registry.each([&](auto entID) {
			Entity entity = { entID, sceneContext.get() };
			if (!entity) return;
			SerializeEntity(entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap; 
		MakeDir(filepath, '/');
		MakeDir(filepath, '\\');
		std::ofstream fout(filepath);
		fout << out.c_str();
	} 
	void SceneSerializer::SerializeRuntime(const std::string& filepath) {
		AW_CORE_ASSERT(false, "SerializeRuntime not implemented");
	}


	bool SceneSerializer::Deserialize(const std::string& filepath) {
		YAML::Node data;
		try {
			data = YAML::LoadFile(filepath);
		} catch (const YAML::ParserException& ex) {
			AW_CORE_ERROR(ex.what());
			return false;
		}
		if (!data["Scene"]) return false;
		
		std::string sceneName = data["Scene"].as<std::string>();
		AW_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities) {
			for (auto entity : entities) {
				uint64_t uuid = entity["Entity ID"].as<uint64_t>();

				std::string name;
				auto tagComponent = entity["Tag"];
				if (tagComponent) name = tagComponent["Tag"].as<std::string>();
				AW_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = sceneContext->CreateEntity(name);

				auto trans = entity["Transform"];
				if (trans) {
					auto& tc = deserializedEntity.Get<CTransform>();
					tc.Position = trans["Position"].as<glm::vec3>();
					tc.Rotation = trans["Rotation"].as<glm::vec3>();
					tc.Scale = trans["Scale"].as<glm::vec3>();
				}



				auto camera = entity["Camera"];
				if (camera) {
					auto& cc = deserializedEntity.Add<CCamera>();
					auto& camProps = camera["Camera Properties"];
					cc.Camera.SetProjectionType((SceneCamera::ProjectionType) camProps["Projection Type"].as<int>());

					cc.Camera.SetPerspectiveFOV(camProps["Perspective FOV"].as<float>());
					cc.Camera.SetPerspectiveNearClip(camProps["Perspective Near"].as<float>());
					cc.Camera.SetPerspectiveFarClip(camProps["Perspective Far"].as<float>());

					cc.Camera.SetOrthographicSize(camProps["Orthographic Size"].as<float>());
					cc.Camera.SetOrthographicNearClip(camProps["Orthographic Near"].as<float>());
					cc.Camera.SetOrthographicFarClip(camProps["Orthographic Far"].as<float>());

					cc.Primary = camera["Primary"].as<bool>();
					cc.FixedAspectRatio = camera["Fixed Aspect Ratio"].as<bool>();

				}

				auto sprite = entity["Sprite Renderer"];
				if (sprite) {
					auto& sr = deserializedEntity.Add<CSpriteRenderer>();
					sr.Color = sprite["Color"].as<glm::vec4>();
				}

			}
		}
		
		return true;
	}
	bool SceneSerializer::DeserializeRuntime(const std::string& filepath) {
		AW_CORE_ASSERT(false, "DeserializeRuntime not implemented");
		return false;
	}
}

