#pragma once
#include "Component.h"


namespace LoveEngine {
	namespace ECS {

		class Transform;
		class Transition : public Component {
		public:
			
			class TransitionBehaviour {
			public:
				Transform* tr;
				virtual bool update() = 0;
			};

			TransitionBehaviour* tb;
			
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf) override;
		};
	}
}

