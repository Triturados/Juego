#include "SceneDefinition.h"
#include <Scene.h>
#include <Component.h>
#include <GameObject.h>
#include <Components/ComponenteDeContar.h>

class EscenaDani : public SceneCreator {

public:
	Scene* populateScene() override {
		auto escena = createScene("Escena dani");
		auto objeto = createGameObject("Objeto de nuesto amigo y vecino Dani");

		objeto->addComponent<ComponenteDeContar>();

		return escena;
	}
};



void SceneDefinitions::scenesDefinitions() {
	escenas.push_back(new EscenaDani());
}