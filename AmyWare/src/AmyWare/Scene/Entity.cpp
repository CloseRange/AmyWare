#include "awpch.h"
#include "Entity.h"

namespace AmyWare {
	Entity::Entity(entt::entity handle, Scene* scene) 
		:handle(handle), scene(scene){
	}
	AmyWare::Entity::~Entity() {
	}
}