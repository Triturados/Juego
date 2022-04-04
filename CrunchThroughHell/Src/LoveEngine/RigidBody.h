#pragma once

#include "Component.h"
#include <string>


class btRigidBody;

namespace LoveEngine {
	namespace Utilities {
		template <typename T>
		class Vector3;
	}
	namespace ECS {
		enum  ForceMode {
			FORCE,
			ACCELERATION,
			IMPULSE,
			VELOCITY_CHANGE
		};

		enum class RBState {
			Kinematic = 0,
			Static = 1,
			Dynamic = 2
		};

		enum class TipoForma {
			Cube = 0,
			Sphere = 1,
			Plane = 2,
			Cylinder = 3,
			Cone = 4
		};

		class Transform;

		class RigidBody : public Component
		{
		
		public:
			void addForce(Utilities::Vector3<float> vel, Utilities::Vector3<float> relativePos, int type);

			void setTransform(Transform* t_);

			void setMass(float mass_);

			void setForma(std::string nameF_);

			void setLinearVelocity(Utilities::Vector3<float> vel);
		};
	};

}