#pragma once
#include <UIContainer.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {

		class ScrollContainer : public UIContainer {
		public:
			ScrollContainer();

			void update() override;
			void onMove() override;
			void receiveMessage(Utilities::StringFormatter&) override;
		private:
			bool automatic;
			int minHeight;
			int maxHeight;
			float speed;
		};
	}
}
