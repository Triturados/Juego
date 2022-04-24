#include "Transition.h"
#include "Image.h"
#include "GameObject.h"
#include "GameTime.h"
#include "StringFormatter.h"
#include "SceneManager.h"
namespace LoveEngine {
	namespace ECS {
		class Fade : public Transition::TransitionBehaviour {

			void update(float t) override {
				img->setOpacity(t);
			}
		};
		Transition::Transition()
		{
			in = true;
			t = 0;
			duration = 0;
			sceneIdx = 0;
			sceneChange = 0;
			img = nullptr;
			tb = nullptr;
		}
		Transition::~Transition()
		{
			if (tb != nullptr)
				delete tb;
		}
		void Transition::init()
		{
			img = gameObject->getComponent<Image>();
			tb->img = img;
		}

		void Transition::update()
		{
			t += Time::getInstance()->deltaTime;

			if (t > duration) {
				enabled = false;
				gameObject->removeGameObject();

				if (!in) {
					SceneManagement::changeScene(sceneIdx, (SceneManagement::SceneLoad)sceneChange);
				}
			}
			
			float val = t / duration;
			val = !in ? val : 1 - val;
			tb->update(val);
		}
		
		void Transition::receiveMessage(Utilities::StringFormatter& sf)
		{
			if (tb == nullptr) {
				delete tb;
				tb = nullptr;
			}

			std::string type = sf.getString("type");

			if (type == "fade") {

				tb = new Fade();
			}
			else {
				tb = new Fade();
			}


			sf.tryGetInt("sceneIdx", sceneIdx);
			sf.tryGetInt("sceneChange", sceneChange);
			sf.tryGetFloat("duration", duration);
			sf.tryGetBool("direction", in);

			if (img != nullptr)
				tb->img = img;
		}
	}





}