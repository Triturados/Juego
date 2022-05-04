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

			GameObject* boss = nullptr;
			GameObject* player;
			GameObject* cam;

			Input::InputManager* input;
			float horiSens = 1;
			float verSens = 1;

			float antAngulo = 180;
			int cont = 0;
			bool girarDer = true;

			bool followBoss;
			float distanceBehindPlayer = 20;
			float distanceAbovePlayer = 6;

			float calculateAngle(Utilities::Vector3<float> vectorA, Utilities::Vector3<float> vectorB);
			void lookAtBoss();
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
