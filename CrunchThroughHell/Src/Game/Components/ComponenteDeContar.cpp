#include "ComponenteDeContar.h"
#include <iostream>
#include <SceneManager.h>

void ComponenteDeContar::update() {

	if (SceneManager::getInstance() != nullptr) {
		std::cout << "SI QUE EXISTE OLE OLE OLE\n";
	}
	else std::cout << (count++) << "\n";
}

