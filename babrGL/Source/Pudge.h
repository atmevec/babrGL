#pragma once
#include "Framework/Sprite.h"
#include "resource1.h"

#define ROW1 484
#define ROW2 561
#define ROW3 638
#define ROW4 715
#define ROW5 792
#define ROW6 869
#define ROW7 946

#define SPRITE1 0
#define SPRITE2 77

class Pudge
{
	public:

	Pudge::Pudge() {
		TextureSample pudgeSample(77, 77, 1, SPRITE1, ROW3);
		Sprite localSprite(pudgeSample,2,300,1000);
		localSprite.SetBounds(3440,0,1400,0);
		walkingLeft = Animation(true, 12);
		walkingRight = Animation(true, 12);
		walkingUp = Animation(true, 12);
		walkingDown = Animation(true, 12);

		Frame Frame1(SPRITE2, ROW1);

		walkingDown.addFrame(Frame1);

		Frame Frame2(SPRITE1, ROW2);
		Frame2.setSound(&walking);

		walkingDown.addFrame(Frame2);

		walkingDown.addFrame(Frame1);

		Frame Frame3(SPRITE2, ROW2);
		Frame3.setSound(&walking);

		walkingDown.addFrame(Frame3);
		
		walkingDown.setDefaultFrame(Frame1);

		
		Frame Frame7(SPRITE1, ROW3);

		walkingUp.addFrame(Frame7);

		Frame Frame8(SPRITE2, ROW3);
		Frame8.setSound(&walking);

		walkingUp.addFrame(Frame8);

		walkingUp.addFrame(Frame7);

		Frame Frame9(SPRITE1, ROW4);
		Frame9.setSound(&walking);

		walkingUp.addFrame(Frame9);

		walkingUp.setDefaultFrame(Frame7);


		Frame Frame10(SPRITE1, ROW5);

		walkingRight.addFrame(Frame10);

		Frame Frame11(SPRITE2, ROW5);
		Frame11.setSound(&walking);

		walkingRight.addFrame(Frame11);

		walkingRight.addFrame(Frame10);

		Frame Frame12(SPRITE2, ROW4);
		Frame12.setSound(&walking);

		walkingRight.addFrame(Frame12);

		walkingRight.setDefaultFrame(Frame10);


		Frame Frame4(SPRITE2, ROW6);

		walkingLeft.addFrame(Frame4);

		Frame Frame5(SPRITE1, ROW6);
		Frame5.setSound(&walking);

		walkingLeft.addFrame(Frame5);

		walkingLeft.addFrame(Frame4);

		Frame Frame6(SPRITE1, ROW7);
		Frame6.setSound(&walking);

		walkingLeft.addFrame(Frame6);

		walkingLeft.setDefaultFrame(Frame4);

		this->localSprite = localSprite;
	};

	Sprite* getSprite() { return &localSprite; };

	void Stop()
	{
		this->localSprite.Stop();
		W = false;
		A = false;
		S = false;
		D = false;
	}

	void Press(GLint key)
	{
		switch (key)
		{
		case GLFW_KEY_D:
			D = true;
			localSprite.setVelocity(10, 0);
			if ((!A && (W == S)))
				localSprite.animate(&walkingRight);
			else if (A && !(W || S))
				localSprite.stopAnimation();
			break;
		case GLFW_KEY_W:
			W = true;
			localSprite.setVelocity(0, 10);
			if ((!S && (A == D)))
				localSprite.animate(&walkingUp);
			else if (S && !(A || D))
				localSprite.stopAnimation();
			break;
		case GLFW_KEY_A:
			A = true;
			localSprite.setVelocity(-10, 0);
			if ((!D && (W == S)))
				localSprite.animate(&walkingLeft);
			else if (D && !(W || S))
				localSprite.stopAnimation();
			break;
		case GLFW_KEY_S:
			S = true;
			localSprite.setVelocity(0, -10);
			if ((!W && (A == D)))
				localSprite.animate(&walkingDown);
			else if (W && !(A || D))
				localSprite.stopAnimation();
			break;
		case GLFW_KEY_SPACE:
			break;
		case GLFW_KEY_R:
			// ULTIMATE YO!

			break;
		}
	}

	void Release(GLint key)
	{
		switch (key)
		{
		case GLFW_KEY_D:
			if (D)
			{
				localSprite.setVelocity(-10, 0);
				if (A && (W == S))
					localSprite.animate(&walkingLeft);
				else if (!A && (S == W))
					localSprite.stopAnimation();
				else if (S && !W)
					localSprite.animate(&walkingDown);
				else if (W && !S)
					localSprite.animate(&walkingUp);
				D = false;
			}
			break;
		case GLFW_KEY_W:
			if (W)
			{
				localSprite.setVelocity(0, -10);
				if (S && (A == D))
					localSprite.animate(&walkingDown);
				else if (!S && (A == D))
					localSprite.stopAnimation();
				else if (A && !D)
					localSprite.animate(&walkingLeft);
				else if (D && !A)
					localSprite.animate(&walkingRight);
				W = false;
			}
			break;
		case GLFW_KEY_A:
			if (A)
			{
				localSprite.setVelocity(10, 0);
				if (D && (W == S))
					localSprite.animate(&walkingRight);
				else if (!D && (S == W))
					localSprite.stopAnimation();
				else if (S && !W)
					localSprite.animate(&walkingDown);
				else if (W && !S)
					localSprite.animate(&walkingUp);
				A = false;
			}
			break;
		case GLFW_KEY_S:
			if (S)
			{
				localSprite.setVelocity(0, 10);
				if (W && (A == D))
					localSprite.animate(&walkingUp);
				if (!W && (A == D))
					localSprite.stopAnimation();
				else if (A && !D)
					localSprite.animate(&walkingLeft);
				else if (D && !A)
					localSprite.animate(&walkingRight);
				S = false;
			}
			break;
		}
	}


private:
	Sprite localSprite;
	Animation walkingLeft, walkingRight, walkingDown, walkingUp;
	GLboolean W = false, A = false, S = false, D = false;
	Sound walking = Sound(SOUND_STEP2);
};