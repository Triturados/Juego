#include "ComponentDefinition.h"
#include <ComponentFactory.h>
#include <cassert>

#include <Components/MovimientoJugador.h>
#include <Components/ComponenteDeContar.h>
#include <Components/ComportamientoBoss.h>
#include <Components/SaludJugador.h>
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
			newComponent<SaludJugador>("SaludJugador");
			newComponent<ComportamientoBoss>("ComportamientoBoss");
			newComponent<MainMenu>("MainMenu");
			newComponent<PauseGame>("PauseGame");
			newComponent<PauseMenu>("PauseMenu");
			newComponent<ShowText>("ShowText");
			newComponent<DeadZone>("DeadZone");
			newComponent<EfectoEscenario>("EfectoEscenario");
			newComponent<DeadMenu>("DeadMenu");
			newComponent<Conversation>("Dialogue");
			newComponent<Conversation>("Conversation");


			inst = nullptr;
		}
	}
}