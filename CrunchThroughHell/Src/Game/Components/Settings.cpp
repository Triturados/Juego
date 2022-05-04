#include "Settings.h"
#include <Button.h>
#include <SceneManager.h>
#include <Window.h>
#include <StringFormatter.h>
#include <SceneManager.h>
LoveEngine::ECS::Settings::Settings()
{
	for (int i = 0; i < 5; i++)
		buttons[i] = nullptr;
}

#define chngRes(x) changeResolution##x()
void LoveEngine::ECS::Settings::init()
{
	/*for (int i = 0; i < resolutions.size(); i++) {

		Button* button = buttons[i];

		if (button != nullptr) {
			button->onClick([&]() {
				changeResolution(resolutions[i - 1]);
				});
		}
	}*/

	if (buttons[1] != nullptr)
		buttons[1]->onClick([&]() {changeResolution0(); });

	if (buttons[2] != nullptr)
		buttons[2]->onClick([&]() {changeResolution1(); });

	if (buttons[3] != nullptr)
		buttons[3]->onClick([&]() {changeResolution2(); });

	if (buttons[4] != nullptr)
		buttons[4]->onClick([&]() {changeResolution3(); });

}

void LoveEngine::ECS::Settings::receiveMessage(Utilities::StringFormatter& sf)
{
	Utilities::Vector3<float> v;
	if (sf.tryGetVector3("resolution", v)) {
		resolutions.push_back((Utilities::Vector3<int>)v);
	}
}

void LoveEngine::ECS::Settings::receiveComponent(int i, Component* c)
{
	Button* button = static_cast<Button*>(c);
	switch (i)
	{
	case 0:
		button->onClick([&]() {backtomenu(); });
		break;
	case 1:
		button->onClick([&]() {alternateFullScreen(); });
		break;
	default:
		if (i < 0) {
			buttons[-i] = button;
			return;
		}
		break;
	}
}

void LoveEngine::ECS::Settings::alternateFullScreen()
{
	Window* window = Window::getInstance();
	window->setFullScreen(!window->isFullScreen());
}

void LoveEngine::ECS::Settings::changeResolution(Utilities::Vector3<int> res)
{
	Window* window = Window::getInstance();
	window->setWindowSize(Utilities::Vec3toVec2Int(res));

	SceneManagement::changeScene(0, SceneManagement::SceneLoad::CLEAR);
}

void LoveEngine::ECS::Settings::changeResolution0()
{
	changeResolution(resolutions[0]);
}

void LoveEngine::ECS::Settings::changeResolution1()
{
	changeResolution(resolutions[1]);
}

void LoveEngine::ECS::Settings::changeResolution2()
{
	changeResolution(resolutions[2]);
}

void LoveEngine::ECS::Settings::changeResolution3()
{
	changeResolution(resolutions[3]);
}

void LoveEngine::ECS::Settings::backtomenu()
{
	SceneManagement::changeScene(0, SceneManagement::SceneLoad::POP);
}
