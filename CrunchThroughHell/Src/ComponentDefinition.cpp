#include "ComponentDefinition.h"
#include <ComponentFactory.h>
#include <cassert>

#include <Components/ComponenteDeContar.h>
namespace LoveEngine {

	void defineComponents() {

		ComponentFactory* inst = ComponentFactory::getInstance();
		assert(inst != nullptr);


		inst->registerComponent(new ComponentCreatorTemplate<ComponenteDeContar>("ComponenteDeContar"));
		inst->registerComponent(new ComponentCreatorTemplate<Autodestruccion>("AutoDestruccion"));
		inst->registerComponent(new ComponentCreatorTemplate<FrameRate>("FrameRate"));
	}

}