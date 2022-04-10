//#pragma once
//#include "Component.h"
//
//
//namespace LoveEngine {
//	namespace Input {
//		class InputManager;
//	}
//
//	namespace Utilities {
//		template<typename T>
//		class Vector2;
//		template<typename T>
//		class Vector3;
//		template<typename T>
//		class Vector4;
//	}
//
//	namespace ECS {
//		class Transform;
//		class Camera;
//		class CamFollow : public Component {
//
//		private:
//			Transform* playerTr;
//			Transform* bossTr;
//			Transform* camTr;
//			Camera* cam;
//
//			GameObject* boss;
//			GameObject* player;
//
//			Input::InputManager* input;
//			float speed = 15;
//			float rotSpeed = 5;
//
//			bool followBoss;
//
//			Utilities::Vector2<float> mousePos;
//
//			float horiSens;
//			float verSens;
//		public:
//			void init() override;
//			void update() override;
//			void receiveGameObject(int n, GameObject* b) override;
//			void receiveMessage(std::string message) override;
//		};
//	}
//}

