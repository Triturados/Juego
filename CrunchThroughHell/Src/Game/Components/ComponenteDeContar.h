#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace ECS {

		class Timer;

		class ComponenteDeContar : public Component {
			int count = 0;
		public:
			void init() override;
			void update() override;
			void receiveMessage(std::string message) override;
		};

		class FrameRate : public Component {
		public:
			void init() override;
			void update() override;
		};


		class Autodestruccion : public Component {
			LoveEngine::ECS::Timer* timer;
		public:
			void init() override;
			void update() override;
		};

		class EscribirNumero : public Component {
			int numerito = 2;
		public:
			void init() override;
			void update() override;

			//void receiveValues(int, float, Component* = nullptr, GameObject* = nullptr);
			void receiveMessage(std::string message) override;
		};


	}
}
