#pragma once
#include <Component.h>

class ComponenteDeContar : public Component {
	int count = 0;
public:
	void init() override;
	void update() override;
};

class FrameRate : public Component {
public:
	void init() override;
	void update() override;
};

class Timer;

class Autodestruccion : public Component {
	Timer* timer;
public:
	void init() override;
	void update() override;
};
