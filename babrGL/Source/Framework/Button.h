#pragma once
#include "Sprite.h"
#include "Menu.h"
#include <functional>

class Button
{
	public:
		Button::Button(TextureSample sample, GLfloat scale, GLfloat posX, GLfloat posY) { privSprite = Sprite(sample, scale, posX, posY); sizeX = sample.GetSizeX() * scale; sizeY = sample.GetSizeY() * scale; this->posX = posX; this->posY = posY; };
		Button::Button() {  };
		Sprite* Button::GetSprite() { return &privSprite; };
		void Button::SetTexture(GLfloat offsetX, GLfloat offsetY) { privSprite.setTexOffset(offsetX, offsetY); }
		void Button::SetPressedFrame(Frame press) { this->pressed = press; };
		void Button::SetUnpressedFrame(Frame unpress) { this->unpressed = unpress; };
		GLboolean Button::Press(GLdouble x, GLdouble y) {
			if (x - posX >= 0 && x - posX <= sizeX)
			{
				if (y - posY >= 0 && y - posY <= sizeY)
				{
					pressedBool = true;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		};
		GLboolean Button::Release(GLdouble x, GLdouble y) {
			if (pressedBool)
			{
				if (x - posX >= 0 && x - posX <= sizeX)
				{
					if (y - posY >= 0 && y - posY <= sizeY)
					{
						return true;
					}
					else return false;
				}
				else
					return false;
			}
			else
				return false;

			pressedBool = false;
		};
		void Button::Reset()
		{
			pressedBool = false;
		}
	private:
		Sprite privSprite;
		Frame pressed, unpressed;
		Animation buttonAnim;
		GLboolean pressedBool = false;
		GLfloat sizeX, sizeY, posX, posY;
};