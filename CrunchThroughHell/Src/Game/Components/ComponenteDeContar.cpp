#include "ComponenteDeContar.h"
#include <iostream>


void ComponenteDeContar::update() {
	std::cout << (count += 2) << "\n";
}