#pragma once
#include <Component.h>


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class RigidBody;
		class Slider;
		class SaludJugador : public Component {
			
		private:
			Transform* tr = nullptr;
			Slider* slider = nullptr;
			Input::InputManager* input = nullptr;

			int _MAX_HEALTH = 4;
			int actHealth = 4;

		public:
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;

			inline int getHealth() { return actHealth; }
			void addHealth();
			void setHealth(int health);
			void addMaxHealth();
		};
	}
}
