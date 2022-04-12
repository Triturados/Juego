#pragma once
#include "Component.h"


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	//namespace Utilities {
	//	template<typename T>
	//	class Vector2;
	//	template<typename T>
	//	class Vector3;
	//	template<typename T>
	//	class Vector4;
	//}

	namespace ECS {
		class Transform;
		class Camera;
		class CamFollow : public Component {

		private:
			Transform* playerTr;
			Camera* cam;
 
			Input::InputManager* input;
		public:
			void init() override;
			void update() override;
			void receiveGameObject(int n, GameObject* b) override;
			void receiveMessage(Utilities::StringFormatter& sf) override;
		};
	}
}

