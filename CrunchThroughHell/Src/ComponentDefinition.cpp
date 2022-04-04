#include "ComponentDefinition.h"
#include <ComponentFactory.h>
#include <cassert>

#include <Components/MovimientoJugador.h>
#include <Components/ComponenteDeContar.h>
namespace LoveEngine {

	using namespace ECS;
	namespace ComponentDefinitions {
		void defineComponents() {

			ComponentFactory* inst = ComponentFactory::getInstance();
			assert(inst != nullptr);

			inst->registerComponent(new ComponentCreatorTemplate<ComponenteDeContar>("ComponenteDeContar"));
			inst->registerComponent(new ComponentCreatorTemplate<Autodestruccion>("AutoDestruccion"));
			inst->registerComponent(new ComponentCreatorTemplate<FrameRate>("FrameRate"));
			inst->registerComponent(new ComponentCreatorTemplate<EscribirNumero>("EscribirNumero"));
			inst->registerComponent(new ComponentCreatorTemplate<MovimientoJugador>("MovimientoJugador"));

		}
	}
}