#pragma once
#pragma once

#include <Components/Interactable.h>

class string;
namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Interactable;
		class StringFormatter;
		class ShowText;
		class Conversation;
	
		class BossDialog : public Interactable {

		private:
			

			Conversation* converBoss1;
			Conversation* alternateConverBoss1;
			Conversation* converBoss2;
			Conversation* alternateConverBoss2;

			bool boss1Defeated = false;
			int bossNum = 1;

		public:

			void init()override;
			void use() override;
		
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int, Component*) override;
			void notOnRangeCallBack();
		};
	}
}
