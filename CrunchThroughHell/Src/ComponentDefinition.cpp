#include "ComponentDefinition.h"
#include <ComponentFactory.h>
#include <cassert>

#include <Components/ComponenteDeContar.h>
namespace LoveEngine {

	class ContarCreator: public ComponentCreator {
	public:
		ContarCreator() : ComponentCreator("ComponenteDeContar"){

		}

		Component* CreateComponent() override {
			return new ComponenteDeContar();
		}
	};

	void defineComponents() {

		ComponentFactory* inst = ComponentFactory::getInstance();
		assert(inst != nullptr);

		inst->registerComponent(new ContarCreator());


	}

}