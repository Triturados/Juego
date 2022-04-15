#pragma once
#include <Component.h>


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class RigidBody;
		class SaludJugador : public Component {
			
		private:
			Transform* tr;
			Input::InputManager* input;

		public:
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
		};
	}
}
