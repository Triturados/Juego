#include "MainMenu.h"
#include <SceneManager.h>
#include <Button.h>
#include <Definitions.h>

namespace LoveEngine {

	enum MenuButtons {
		NewGame, Continue, HowToPlay, Settings, About, Exit, NumButtons
	};

	namespace ECS {
		MainMenu::MainMenu()
		{
			buttons = std::vector<Button*>(MenuButtons::NumButtons, nullptr);
		}
		void MainMenu::init()
		{
			buttons[MenuButtons::NewGame]->onClick([&]() {newGame(); });
			buttons[MenuButtons::Continue]->onClick([&]() {continueGame(); });
			buttons[MenuButtons::HowToPlay]->onClick([&]() {howToPlay(); });
			buttons[MenuButtons::Settings]->onClick([&]() {settings(); });
			buttons[MenuButtons::About]->onClick([&]() {about(); });
			buttons[MenuButtons::Exit]->onClick([&]() {exit(); });
		}
		void MainMenu::receiveComponent(int i, Component* c)
		{
			buttons[i] = static_cast<Button*>(c);
		}


		void MainMenu::newGame() {
			SceneManagement::changeScene((int)SceneOrder::Overworld, SceneManagement::SceneLoad::SWAP);
		}

		void MainMenu::continueGame() {

		}

		void MainMenu::howToPlay() {

		}

		void MainMenu::settings() {

		}
		
		void MainMenu::about() {

		}

		void MainMenu::exit() {
			SceneManagement::changeScene(0, SceneManagement::SceneLoad::EXIT);
		}

	}
}