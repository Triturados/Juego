#include "ComponentDefinition.h"
#include <ComponentFactory.h>
#include <cassert>

#include <Components/MovimientoJugador.h>
#include <Components/ComponenteDeContar.h>
#include <Components/BossMelee.h>
#include <Components/BossDistancia.h>
#include <Components/Salud.h>
#include "Components/CamFollow.h"
#include "Components/MainMenu.h"
#include "Components/CamRotate.h"
#include "Components/ShowText.h"
#include "Components/DeadZone.h"
#include "Components/EfectoEscenario.h"
#include "Components/DeadMenu.h"
#include "Components/PauseGame.h"
#include "Components/PauseMenu.h"
#include "Components/Conversation.h"
#include "Components/Transition.h"
#include "Components/Bullet.h"
#include "Components/Stamina.h"
#include "Components/AtaqueJugador.h"
#include "Components/BulletGenerator.h"
#include "Components/MoveUI.h"

namespace LoveEngine {

	using namespace ECS;
	namespace ComponentDefinitions {

		ComponentFactory* inst = nullptr;

		template <class t>
		void newComponent(std::string name) {
			inst->registerComponent(new ComponentCreatorTemplate<t>(name));
		}

		void defineComponents() {

			inst = ComponentFactory::getInstance();
			assert(inst != nullptr);

			newComponent<ComponenteDeContar>("ComponenteDeContar");
			newComponent<Autodestruccion>("Autodestruccion");
			newComponent<FrameRate>("FrameRate");
			newComponent<EscribirNumero>("EscribirNumero");
			newComponent<MovimientoJugador>("MovimientoJugador");
			newComponent<Moverpanatalla>("MoverPantalla");
			newComponent<CamFollow>("CamFollow");
			newComponent<CamRotate>("CamRotate");
			newComponent<Salud>("Salud");
			newComponent<BossMelee>("BossMelee");
			newComponent<BossDistancia>("BossDistancia");
			newComponent<MainMenu>("MainMenu");
			newComponent<PauseGame>("PauseGame");
			newComponent<PauseMenu>("PauseMenu");
			newComponent<ShowText>("ShowText");
			newComponent<DeadZone>("DeadZone");
			newComponent<EfectoEscenario>("EfectoEscenario");
			newComponent<DeadMenu>("DeadMenu");
			newComponent<Conversation>("Dialogue");
			newComponent<Conversation>("Conversation");
			newComponent<Transition>("Transition");
			newComponent<Bullet>("Bullet");
			newComponent<BulletGenerator>("BulletGenerator");
			newComponent<Stamina>("Stamina");
			newComponent<MoveUI>("MoveUI");
			newComponent<AtaqueJugador>("AtaqueJugador");

			inst = nullptr;
		}
	}
}