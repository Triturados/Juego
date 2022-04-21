#pragma once
#include <Component.h>
#include <functional>

namespace LoveEngine {

	namespace ECS {
		class Text;

		class ShowText : public Component {
		public:
			ShowText();
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf) override;
			void receiveString(std::string str) override;

			void setCallBack(std::function<void()> f);
			void changeText(std::string str);
			void completeText();
			bool hasFinishedWritting();
		private:
			Text* text;

			bool finished;
			int currentIdx;
			float t, interval;
			std::string finalText;
			std::string currentText;
			std::function<void()> onEnd;
		};
	}
}
