#pragma once
#include <UIContainer.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {

		class ScrollContainer : public UIContainer {
		public:
			ScrollContainer();
			
			void init() override;
			void update() override;
			void onMove() override;
			void receiveMessage(Utilities::StringFormatter&) override;
			void receiveComponent(int, Component*) override;
		private:
			bool automatic;
			int minHeight;
			int maxHeight;
			float currentHeight;
			float speed;
			float timeToEnable;

			UIContainer* cont;
		};
	}
}
