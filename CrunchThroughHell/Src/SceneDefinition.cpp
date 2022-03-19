#include "SceneDefinition.h"
#include <Scene.h>
#include <Component.h>
#include <GameObject.h>
#include <iostream>


class ComponenteDani : public Component {
	int count = 0;
public:
	void update() override {
		std::cout << (count += 2) << "\n";
	}
};


class EscenaDani : public SceneCreator {

public:
	Scene* populateScene() override {
		auto escena = createScene("Escena dani");
		auto objeto = createGameObject("Componente dani");

		objeto->addComponent<ComponenteDani>();

		return escena;
	}
};



void SceneDefinitions::scenesDefinitions() {
	escenas.push_back(new EscenaDani());
}