#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace ECS {

		class MovimientoJugador : public Component {
			
			class Transform;
			class InputManager;
		
		private:
			Transform* player;
			InputManager* input;

		public:
			void init() override;
			void update() override;
		};
	}
}
