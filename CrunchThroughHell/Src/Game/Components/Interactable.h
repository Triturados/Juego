#pragma once
#pragma once
#include <Component.h>

class string;
namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class StringFormatter;
		class Transform;
		class ShowText;
		class GameObject;
		class Interactable : public Component {

		protected:

			Input::InputManager* input;

			Transform* tr = nullptr;
			Transform* playerTr = nullptr;

			float interactDistance = 55;

			int interactKey;

			bool justEntered = false;

			ShowText* texto;
			std::string textoOri;

		public:
			void init() override;
			void postInit() override;
			void update() override;
			bool checkDistance();
			void showMessage();
			virtual void use() {};
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int, Component*) override;
			virtual void notOnRangeCallBack() {};

		};
	}
}
