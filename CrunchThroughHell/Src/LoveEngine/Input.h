#pragma once

#include <Vector2.h>
#include <vector>

namespace LoveEngine {
	namespace ECS {
		class Component;
	}

	namespace Input {
		struct  tecla {
			bool pressedLastFrame = false;
			bool beingPressed = false;
			bool keyUp = false;
			std::vector<ECS::Component*> suscriptores;
		};

		enum class InputKeys {
			A = 4, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			RIGHT = 80, LEFT, DOWN, UP, TAB = 43, CTRL = 224, SHIFT = 225,
			SPACE = 44, ESCAPE = 41, ENTER = 88
		};

		enum class  MouseState {
			NONE, CLICK_L, CLICK_R, CLICK_M
		};

		const int controllerButtonCount = 15;
		enum class ControllerButton {
			A, B, X, Y, BACK, GUIDE, START,
			LSTICK, RSTICK, LS, RS,
			DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
			LB, LT, RB, RT
		};

		enum class psControllerButton {
			X, CIRCLE, TRIANGLE, SQUARE, BACK, GUIDE, START,
			LSTICK, RSTICK, LS, RS,
			DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
			LB, LT, RB, RT
		};

		enum class ControllerButtonState {
			UP, DOWN, HOLD, NONE
		};

		struct Controller
		{
			Utilities::Vector2<float> leftJoystick, rightJoystick;
			float leftTrigger, rightTrigger;
			ControllerButtonState buttons[controllerButtonCount];
		};


		class  InputManager {
		public:
			InputManager();
			static void setSDLwithOgreTest();
			static void initSDLWindowTest();
			static InputManager* getInstance();
			bool handleInput();
			bool isKeyPressed(InputKeys key);
			bool keyJustPressed(InputKeys key);

			Controller& getController();
			bool controllerConected();
			Utilities::Vector2<float> mousePosition();
		};
	}
}

