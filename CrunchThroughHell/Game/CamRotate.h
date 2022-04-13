#pragma once
#include <Component.h>


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class CamRotate : public Component {

		private:
			Transform* playerTr;
			Transform* bossTr;
			Transform* camTr;

			GameObject* boss;
			GameObject* player;
			GameObject* cam;

			Input::InputManager* input;
			float horiSens = 1;
			float verSens = 1;

			float antAngulo = 181;
			bool girarDer = true;

			bool followBoss;

			Utilities::Vector2<float>* mousePos;
		public:
			~CamRotate();

			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveGameObject(int n, GameObject* b) override;
		};
	}
}
