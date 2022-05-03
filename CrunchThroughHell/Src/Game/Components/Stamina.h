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
		class Stamina : public Component {
			
		private:
			Transform* tr = nullptr;
			Slider* sliderBehind = nullptr;
			Slider* sliderTop = nullptr;
			Input::InputManager* input = nullptr;

			int _MAX_STAMINA = 100;
			int actStamina = 100;

			float naive_lerp(float a, float b, float t);

			float restartStamina = 0;
			float staminaTime = 3; 
			float comebackStamina;
		public:
			void init() override;
			void update() override;
			virtual void stepPhysics() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int i, Component* c) override;
			
			inline int getMaxStamina() { return _MAX_STAMINA; }
			inline int getStamina() { return actStamina; }
			void addHealth();
			void setStamina(int stamina);
			void loseStamina(int sta);
			~Stamina();
		};
	}
}
