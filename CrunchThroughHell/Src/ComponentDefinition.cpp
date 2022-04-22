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

namespace LoveEngine {

	using namespace ECS;
	namespace ComponentDefinitions {

		template <class t>
		void newComponent(std::string name, ComponentFactory* inst) {
			inst->registerComponent(new ComponentCreatorTemplate<t>(name));
		}

		void defineComponents() {

			ComponentFactory* inst = ComponentFactory::getInstance();
			assert(inst != nullptr);

			newComponent<ComponenteDeContar>("ComponenteDeContar", inst);
			newComponent<Autodestruccion>("Autodestruccion", inst);
			newComponent<FrameRate>("FrameRate", inst);
			newComponent<EscribirNumero>("EscribirNumero", inst);
			newComponent<MovimientoJugador>("MovimientoJugador", inst);
			newComponent<Moverpanatalla>("MoverPantalla", inst);
			newComponent<CamFollow>("CamFollow", inst);
			newComponent<CamRotate>("CamRotate", inst);
			newComponent<SaludJugador>("SaludJugador", inst);
			newComponent<ComportamientoBoss>("ComportamientoBoss", inst);
			newComponent<MainMenu>("MainMenu", inst);
			newComponent<ShowText>("ShowText", inst);
			newComponent<DeadZone>("DeadZone", inst);
			newComponent<EfectoEscenario>("EfectoEscenario", inst);
			newComponent<DeadMenu>("DeadMenu", inst);

			/*inst->registerComponent(new ComponentCreatorTemplate<ComponenteDeContar>("ComponenteDeContar"));
			inst->registerComponent(new ComponentCreatorTemplate<Autodestruccion>("AutoDestruccion"));
			inst->registerComponent(new ComponentCreatorTemplate<FrameRate>("FrameRate"));
			inst->registerComponent(new ComponentCreatorTemplate<EscribirNumero>("EscribirNumero"));
			inst->registerComponent(new ComponentCreatorTemplate<MovimientoJugador>("MovimientoJugador"));
			inst->registerComponent(new ComponentCreatorTemplate<Moverpanatalla>("MoverPantalla"));
			inst->registerComponent(new ComponentCreatorTemplate<CamFollow>("CamFollow"));
			inst->registerComponent(new ComponentCreatorTemplate<CamRotate>("CamRotate"));
			inst->registerComponent(new ComponentCreatorTemplate<ComportamientoBoss>("ComportamientoBoss"));
			inst->registerComponent(new ComponentCreatorTemplate<SaludJugador>("SaludJugador"));
			inst->registerComponent(new ComponentCreatorTemplate<MainMenu>("MainMenu"));
			inst->registerComponent(new ComponentCreatorTemplate<ShowText>("ShowText"));*/
		}
	}
}