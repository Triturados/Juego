#pragma once
#include <Component.h>


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class MovimientoJugador : public Component {
			
		private:
			Transform* player;
			Input::InputManager* input;
			float speed = 15;
			float rotSpeed = 5;

		public:
			void init() override;
			void update() override;
			void receiveMessage(std::string message) override;
		};
	}
}
