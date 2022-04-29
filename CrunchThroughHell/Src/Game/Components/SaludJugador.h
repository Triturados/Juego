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
			Slider* sliderBehind = nullptr;
			Slider* sliderTop = nullptr;
			Input::InputManager* input = nullptr;

			int _MAX_HEALTH = 100;
			int actHealth = 100;

			bool hitCooldown = false;
			float _MAX_COOLDOWN_TIME = 0.3;
			float cooldownTime = _MAX_COOLDOWN_TIME;

		public:
			void init() override;
			void update() override;
			virtual void stepPhysics() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int i, Component* c) override;

			inline int getHealth() { return actHealth; }
			void addHealth();
			void setHealth(int health);
			void addMaxHealth();
			void takeDamage(int damage);
			~SaludJugador();
		};
	}
}
