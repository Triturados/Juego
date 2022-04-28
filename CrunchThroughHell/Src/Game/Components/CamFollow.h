#pragma once
#include "Component.h"


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace Utilities {
		template<typename T>
		class Vector3;
	}

	namespace ECS {
		class Transform;
		class Camera;
		class CamFollow : public Component {

		private:
			Transform* targetTr;
			Camera* cam;
 
			Input::InputManager* input;
		public:
			void init() override;
			void update() override;
			void receiveComponent(int n, Component* c) override;
			void receiveMessage(Utilities::StringFormatter& sf) override;
		};
	}
}

