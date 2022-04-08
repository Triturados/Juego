#include <Windows.h>
#include "ComponentDefinition.h"

extern "C" {
	
	__declspec(dllexport) void componentDefinition() {
		LoveEngine::ComponentDefinitions::defineComponents();
	}

	__declspec(dllexport) const char* gameName() {
		return "Crunch Through hell";
	}
}



