#include <Windows.h>
#include "SceneDefinition.h"
#include "ComponentDefinition.h"

extern "C" {
	__declspec(dllexport) SceneDefinitions* quierounaescena() {
		auto scenedef = new SceneDefinitions();
		scenedef->scenesDefinitions();
		return scenedef;
	}
	__declspec(dllexport) void componentDefinition() {
		LoveEngine::defineComponents();
	}
}



