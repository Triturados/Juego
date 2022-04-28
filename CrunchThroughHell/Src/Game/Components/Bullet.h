#pragma once
#include <Component.h>


namespace LoveEngine {

	namespace ECS {
		class Timer;
		class RigidBody;
		class Transform;
		class Mesh;
		class Bullet : public Component {
			
		private:
			Timer* lifetime = nullptr;
			Transform* tr;
			Mesh* mesh;
			Utilities::Vector3<float>* dir;
			float vel;
			int damage;
		public:
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf) override;
			void enterCollision(GameObject* other) override;
		};
	}
}
