#pragma once
#include "Framework/Sprite.h"
#include "resource1.h"

class Alex
{
	public:
		Alex::Alex() {
			//Sprite localSprite(375, 430, 75, 86, 1, 1000, 1000, 0, 225);
			walkingLeft = Animation(true, 14);
			walkingRight = Animation(true, 14);


			Frame Frame1(0, 225);
			walkingRight.addFrame(Frame1);

			Frame Frame2(75, 225);
			Frame2.setSound(&walking);

			walkingRight.addFrame(Frame2);

			walkingRight.addFrame(Frame1);

			Frame Frame3(0, 311);
			Frame3.setSound(&walking);

			walkingRight.addFrame(Frame3);

			walkingRight.setDefaultFrame(Frame1);

			Frame Frame4(75, 311);
			walkingLeft.addFrame(Frame4);

			Frame Frame5(0, 397);
			Frame5.setSound(&walking);

			walkingLeft.addFrame(Frame5);

			walkingLeft.addFrame(Frame4);

			Frame Frame6(75, 397);
			Frame6.setSound(&walking);

			walkingLeft.addFrame(Frame6);

			walkingLeft.setDefaultFrame(Frame4);

			this->localSprite = localSprite;
		};
		Sprite* getSprite() { return &localSprite; };

		void Press(GLint key)
		{
			switch (key)
			{
			case GLFW_KEY_D:
				D = true;
				localSprite.stopAnimation();
				localSprite.setVelocity(10, 0);
				if (!A)
					localSprite.animate(&walkingRight);
				break;
			case GLFW_KEY_W:

				break;
			case GLFW_KEY_A:
				A = true;
				localSprite.stopAnimation();
				localSprite.setVelocity(-10, 0);
				if (!D)
					localSprite.animate(&walkingLeft);
				break;
			case GLFW_KEY_S:

				break;
			case GLFW_KEY_SPACE:
				//this->getSprite()->fade(0, 0.01f, .2f);
				break;
			}
		}

		void Release(GLint key)
		{
			switch (key)
			{
			case GLFW_KEY_D:
				localSprite.setVelocity(-10, 0);
				localSprite.stopAnimation();
				if (A)
					localSprite.animate(&walkingLeft);
				D = false;
				break;
			case GLFW_KEY_W:
				break;
			case GLFW_KEY_A:
				A = false;
				localSprite.setVelocity(10, 0);
				localSprite.stopAnimation();
				if (D)
					localSprite.animate(&walkingRight);
				break;
			case GLFW_KEY_S:
				break;
			}
		}



	private:
		GLboolean A = false, D = false;
		Sprite localSprite;
		Animation walkingLeft, walkingRight;
		Sound walking = Sound(SOUND_STEP2);
};