#include "ShowText.h"
#include <Text.h>
#include <GameObject.h>
#include <Component.h>
#include <cassert>
#include <StringFormatter.h>
#include <GameTime.h>

unsigned int LoveEngine::ECS::Component::numOfComponentClasses = 0;

LoveEngine::ECS::ShowText::ShowText()
{
	text = nullptr;
	t = 0;
	currentIdx = 0;
	interval = 0.1f;
	finished = false;
	currentText = finalText = "";
	onEnd = []() {};
}

void LoveEngine::ECS::ShowText::init()
{
	text = gameObject->getComponent<Text>();
	assert(text != nullptr);
}

void LoveEngine::ECS::ShowText::update()
{
	t += Time::getInstance()->deltaTime;

	if (t > interval) {
		t = 0;
		currentText+= finalText[currentIdx++];
		text->changeText(currentText);
		if (currentIdx >= finalText.size()) {
			enabled = false;
			finished = true;
			onEnd();
		}
	}
}

void LoveEngine::ECS::ShowText::receiveMessage(Utilities::StringFormatter& sf)
{
	if (!sf.tryGetFloat("interval", interval)) {
		int i;
		if (sf.tryGetInt("interval", i)) {
			interval = i;
		}
	}

	sf.tryGetString("text", finalText);
}

void LoveEngine::ECS::ShowText::receiveString(const std::string& str)
{
	finalText = str;
}

void LoveEngine::ECS::ShowText::setCallBack(std::function<void()> f)
{
	onEnd = f;
}

void LoveEngine::ECS::ShowText::changeText(std::string str)
{
	currentText = "";
	currentIdx = 0;
	finalText = str;
	t = 0;
	finished = false;
	enabled = true;
}

void LoveEngine::ECS::ShowText::completeText()
{
	finished = true;
	enabled = false;
	currentIdx = finalText.size();
	currentText = finalText;
	text->changeText(currentText);
}

bool LoveEngine::ECS::ShowText::hasFinishedWritting()
{
	return finished;
}
