#pragma once
#include <Component.h>

class ComponenteDeContar : public Component {
	int count = 0;
public:
	void init() override;
	void update() override;
};
