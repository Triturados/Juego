#pragma once
#include <Component.h>
#include <Vector2.h>

namespace LoveEngine {
	namespace ECS {
		class Image;
		class Button;

		class ScaleMainMenuButton : public Component {
		private:
			float maxDistance;
			float height;
			Utilities::Vector2<int> originalScale;

			Button* button;
		public:
			ScaleMainMenuButton();
			void init() override;
			void setHeight(float);
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf);
		};

	}
}