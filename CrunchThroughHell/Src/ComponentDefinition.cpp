#include "ComponentDefinition.h"
#include <ComponentFactory.h>
#include <cassert>

#include <Components/ComponenteDeContar.h>
namespace LoveEngine {

	class ContarCreator: public ComponentCreator {
	public:
		ContarCreator() : ComponentCreator("ComponenteDeContar"){}
		Component* CreateComponent() override { return new ComponenteDeContar(); }
	};

	class AutodestruccionCreator : public ComponentCreator {
	public:
		AutodestruccionCreator() : ComponentCreator("Autodestruccion") {}
		Component* CreateComponent() override { return new Autodestruccion(); }
	};

	class FrameRateCreator : public ComponentCreator {
	public:
		FrameRateCreator() : ComponentCreator("FrameRate") {}
		Component* CreateComponent() override { return new FrameRate(); }
	};


	void defineComponents() {

		ComponentFactory* inst = ComponentFactory::getInstance();
		assert(inst != nullptr);

		inst->registerComponent(new ContarCreator());
		inst->registerComponent(new AutodestruccionCreator());
		inst->registerComponent(new FrameRateCreator());
	}

}