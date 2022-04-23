#include "Conversation.h"
#include "GameObject.h"
#include "ShowText.h"
#include "Input.h"
#include "StringFormatter.h"


LoveEngine::ECS::Conversation::Conversation()
{
	lines = 0;
	dialogueIdx = lineIdx = 0;
	showtext = std::vector<ShowText*>(6, nullptr);
	nameText = nullptr;
	onEnd = []() {};
}

void LoveEngine::ECS::Conversation::init()
{
	for (int i = 1; i < lines; i++) {
		showtext[i]->setActive(false);
	}
	showtext[0]->changeText(dialogues[dialogueIdx].message[0]);
}

void LoveEngine::ECS::Conversation::update()
{
	if (dialogueIdx >= dialogues.size()) {
		enabled = false;
		return;
	}
	
	if (Input::InputManager::getInstance()->keyJustPressed(Input::InputKeys::C)) {
		skip();
		return;
	}

	if (lineIdx >= lines)
		return;

	if (showtext[lineIdx]->hasFinishedWritting()) {
		lineIdx++;
		if (lineIdx < lines) {
			showtext[lineIdx]->changeText(dialogues[dialogueIdx].message[lineIdx]);
		}
	}
}


void LoveEngine::ECS::Conversation::receiveMessage(Utilities::StringFormatter& sf)
{
	if (sf.tryGetInt("lines", lines)) {
		showtext = std::vector<ShowText*>(lines, nullptr);
	}

	sf.tryGetString("name", speaker);

	Dialogue d;
	std::string image;
	bool hasContent = false;
	for (int i = 0; i < showtext.size(); i++) {
		std::string line = "line" + std::to_string(i);
		std::string message = "";
		if (sf.tryGetString(line, message)) {
			hasContent = true;
		}
		
		d.message.push_back(message);
	}

	d.speaker = speaker;
	sf.tryGetString("image", d.imageMaterial);

	if (hasContent)
		dialogues.push_back(d);
}

void LoveEngine::ECS::Conversation::receiveComponent(int idx, Component* comp)
{
	if (idx < 0) {
		nameText = static_cast<ShowText*>(comp);
		return;
	}

	showtext[idx] = static_cast<ShowText*>(comp);
}

void LoveEngine::ECS::Conversation::setCallBack(std::function<void()> f)
{
	onEnd = f;
}

void LoveEngine::ECS::Conversation::skip()
{
	if (lineIdx < lines) {
		for (int i = 0; i < lines; i++) {
			showtext[i]->changeText(dialogues[dialogueIdx].message[i]);
			showtext[i]->completeText();
		}
		lineIdx = lines;
	}
	else {
		advanceDialogue();
	}
}

void LoveEngine::ECS::Conversation::clearText()
{
	for (int i = 0; i < lines; i++) {
		showtext[i]->changeText("");
		showtext[i]->completeText();
	}

}

void LoveEngine::ECS::Conversation::advanceDialogue()
{
	clearText();
	lineIdx = 0;
	++dialogueIdx;
	if (dialogueIdx >= dialogues.size()) {
		onEnd();
		enabled = false;
	}
	else
	showtext[0]->changeText(dialogues[dialogueIdx].message[0]);
}
