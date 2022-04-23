#pragma once
#include <Component.h>


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

			float antAngulo = 180;
			int cont = 0;
			bool girarDer = true;

			bool followBoss;

			Utilities::Vector2<float>* mousePos;

			float calculateAngle(Utilities::Vector3<float> vectorA, Utilities::Vector3<float> vectorB);
		public:
			~CamRotate();

			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveGameObject(int n, GameObject* b) override;
			void onSceneUp() override;
			void onSceneDown() override;
		};
	}
}
