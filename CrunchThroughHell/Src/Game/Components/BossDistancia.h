#pragma once
#include "ComportamientoBoss.h"


namespace LoveEngine {

	namespace ECS {
        class ParticleSystem;
        class Sound;
        class Salud;
		class BossDistancia : public ComportamientoBoss {
		protected:
#pragma region Actions
            Sound* deathSound;

			class RangedAttack : public Action
			{
			public:
                RangedAttack(Agent* agent_);
				void setTarget(Transform* t);
				void setTransform(Transform* t);
				bool conditionsFulfilled() const final;
				void onActionStart() final;
				void activeUpdate() final;
                void setAnim(Animation* a);

			protected:
				Transform* target = nullptr;
				Transform* tr = nullptr;
                Animation* anim = nullptr;
                
                struct SpellAnimation {
                    std::string animation;
                    float duration;
                };

                SpellAnimation spellAnimations[3] = { { "spell1", 2.4 }, { "spell2", 1.5 }, { "spell3", 2.66 } };
                int numAnimations = 3;
                int comboIndex = 0;

                void shotOneBullet(Utilities::Vector3<float> dir_);
                void createBullets();
                void attackFinished();
			};

            class KeepDistance : public Action
            {
            public:
                KeepDistance(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void activeUpdate() final;
                void onActionStart() final;
                void setAnim(Animation* a);
            protected:
                float maxVel = 25;
                float acc = 10;
                
                RigidBody* rb = nullptr;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
            };

            class Teleport : public Action
            {
            public:
                bool isTP = false;
                Teleport(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                bool conditionsFulfilled() const final;
                void onActionStart() final;
                void setAnim(Animation* a);
                void setPartSys(ParticleSystem* ps_);
            private:
                void particleTP();
                void startTP();
                void endTP();
            protected:
                ParticleSystem* tpParticles;
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
                Utilities::Vector2<float> posRand();
                int numRandNegPos(int maxRand);
            };

            class Death : public Action
            {
            public:
                Death(Agent* agent_);
                void setDeath(int p);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void setTarget(Transform* t);
                void setAnim(Animation* a);
                void onActionStart() final;
                void setSound(Sound* s) { deathSound = s; }
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
                Sound* deathSound;
            private:
                void startDeath();
                void Died();
            };

#pragma endregion
            void setTargets() override;
		private:
			Transform* tr;
            RangedAttack* attack;
            KeepDistance* keepDistance;
            Teleport* teleport;
            Death* death;
            Salud* salud;
		public:
            int vida;
            int lastVd;
            BossDistancia();
            void init() override;
            void update() override;
		};
	}
}
