#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		/*class Transform;
		class RigidBody;*/
		class ParticleSystem;
		class Animation;
		class AtaqueJugador : public Component {

		private:

			Input::InputManager* input;
			float dmg = 15;

			ParticleSystem* particleSys;
			Animation* attackAnim;

		public:
			void init() override;
			void postInit() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int, Component*) override;
		};
	}
}
