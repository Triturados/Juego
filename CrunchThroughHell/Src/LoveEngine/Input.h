#pragma once

#include <vector>

namespace LoveEngine {
	namespace ECS {
		class Component;
	}

	namespace Utilities {
		template <class T>
		class Vector2;
	}

	namespace Input {
		struct  tecla {
			bool pressedLastFrame = false;
			bool beingPressed = false;
			bool keyUp = false;
			std::vector<ECS::Component*> suscriptores;
		};

		enum class  InputKeys {
			A = 4, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			RIGHT = 80, LEFT, DOWN, UP, TAB = 43, CTRL = 224, SHIFT = 225,
			SPACE = 205, ESCAPE = 41, ENTER = 88
		};

		enum class  MouseState {
			NONE, CLICK_L, CLICK_R, CLICK_M
		};

		class  InputManager {
		public:
			static InputManager* getInstance();
			
			bool isKeyPressed(InputKeys key);
			Utilities::Vector2<float> mousePosition();
		};
	}
}

