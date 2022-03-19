#include <Windows.h>
#include "SceneDefinition.h"

extern "C" {
	__declspec(dllexport) SceneDefinitions* quierounaescena() {
		auto scenedef = new SceneDefinitions();
		scenedef->scenesDefinitions();
		return scenedef;
	}
}



