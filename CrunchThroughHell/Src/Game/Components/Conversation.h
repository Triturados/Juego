#pragma once
#include <Component.h>
#include <functional>
#include <vector>

namespace LoveEngine {

	namespace ECS {
		class Image;
		class ShowText;
		class Conversation : public Component {

			struct Dialogue {
				std::string speaker;
				std::vector<std::string> message;
				std::string imageMaterial;
			};

		public:
			Conversation();
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf) override;
			void receiveComponent(int idx, Component* comp) override;
			void setCallBack(std::function<void()> f);
			void start();
			void clearText();
		private:

			int lines;
			int lineIdx;
			int dialogueIdx;

			ShowText* nameText;
			std::string speaker;
			std::vector<Dialogue> dialogues;
			std::vector<ShowText*> showtext;
			std::function<void()> onEnd;

			void skip();
			void advanceDialogue();
		};
	}
}
