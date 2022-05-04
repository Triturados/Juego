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
			RigidBody* rb;
			Utilities::Vector3<float>* dir;
			Utilities::Vector3<float>* lastPos;
			float vel;
			int damage;
			bool hit = false;
			GameObject* hitObject;

			void bulletDamage(GameObject* other);
		public:
			Bullet();
			~Bullet();
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf) override;
			void colliding(GameObject* other) override;
			void enterCollision(GameObject* other) override;

			void setDir(Utilities::Vector3<float> dir_);
		};
	}
}
