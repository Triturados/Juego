#pragma once
#include "Component.h"


namespace LoveEngine {
	namespace ECS {

		class Image;
		class Transition : public Component {
		public:
			class TransitionBehaviour {
			public:
				Image* img;
				virtual void update(float t) = 0;
			};
			Transition();
			~Transition();
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf) override;

		private:
			bool in;
			int sceneIdx, sceneChange;
			float t;
			float duration;


			Image* img;
			TransitionBehaviour* tb;
		};
	}
}

