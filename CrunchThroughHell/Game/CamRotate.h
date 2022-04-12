//#pragma once
//#include <Component.h>
//
//
//namespace LoveEngine {
//	namespace Input {
//		class InputManager;
//	}
//
//	namespace ECS {
//		class Transform;
//		class CamRotate : public Component {
//
//		private:
//			Transform* playerTr;
//			Transform* bossTr;
//			Transform* camTr;
//
//			GameObject* boss;
//			GameObject* player;
//
//			Input::InputManager* input;
//			float speed = 15;
//			float rotSpeed = 5;
//			float horiSens = 1;
//			float verSens = 1;
//
//			bool followBoss;
//
//			Utilities::Vector2<float> mousePos;
//		public:
//			void init() override;
//			void update() override;
//			void receiveMessage(Utilities::StringFormatter& message) override;
//			void receiveGameObject(int n, GameObject* b) override;
//		};
//	}
//}
