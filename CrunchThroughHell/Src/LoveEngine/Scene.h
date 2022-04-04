#pragma once
#include <string>

namespace LoveEngine {

	namespace ECS {

		class GameObject;
		class Scene final {
	
		public:
			std::string name;
			void setName(std::string newname);
			GameObject* createGameObject(std::string name = "new game object");
		};
	}
}