#pragma once



namespace LoveEngine {
	namespace ECS {
		class Scene;
	}

	namespace SceneManagement {
		class SceneFactory;

		/// <summary>
		/// =PUSH  : ADD THE NEW SCENE AT THE TOP OF THE STACK
		/// =POP   : REMOVE THE SCENE AT THE TOP OF THE STACK
		/// =CLEAR : REMOVES ALL PREVIOUS SCENE AND CREATES THE NEW ONE
		/// =SWAP  : REMOVE THE SCENE AT THE TOP OF THE STACK AND CREATES THE NEW ONE
		/// =EXIT  : STOPS THE GAME
		/// </summary>
		enum class SceneLoad {
			PUSH, SWAP, POP, CLEAR, EXIT
		};

		
		class SceneManager final {
		public:
			static  SceneManager* getInstance();

			ECS::Scene* getCurrentScene();

			//N�mero de escenas totales
			int sceneCount() const;

			//�ndice o nombre de la escena actual
			int         currentSceneIdx() const;
			std::string currentSceneName() const;

			//Cu�ntas escenas hay ahora mismo en la pila
			int stackedScenes() const;

			//Cambiar a una escena dado su �ndice, indicando el tipo de cambio de escena
			void changeScene(int SceneIdx, SceneLoad type);

		};
		
		
		void changeScene(int idx, SceneManagement::SceneLoad scenechangetype);
	}

	
}
