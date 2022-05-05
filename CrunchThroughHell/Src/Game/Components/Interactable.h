#pragma once
#pragma once
#include <Component.h>

class string;
namespace LoveEngine {
	namespace Input {
		class InputManager;
		enum class InputKeys;
	}

	namespace ECS {
		class StringFormatter;
		class Transform;
		class ShowText;
		class GameObject;
		class Interactable : public Component {

		private:

			Input::InputManager* input;
			
			Transform* tr = nullptr;
			Transform* playerTr = nullptr;

			float interactDistance = 15;

			Input::InputKeys interactKey = Input::InputKeys::E;

			ShowText* texto;

		public:
			void init() override;
			void update() override;
			bool checkDistance();
			void showMessage();
			virtual void use(){};
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int, Component*) override;

		};
	}
}
