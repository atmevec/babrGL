#pragma once

#include "Level.h"
#include "Button.h"

class Menu
{
	public:
		Menu::Menu(TextureSample sample, Layer* privLayer) { 
			this->privLayer = privLayer;
			menSprite = Sprite(sample, privLayer->getX() *2 , privLayer->getY() * 2,0,0); };
		Menu::Menu(TextureSample sample, GLfloat sizeX, GLfloat sizeY, GLboolean fadeIn, Layer* privLayer) {
			this->privLayer = privLayer; 
			this->fadeIn = fadeIn;
			menSprite = Sprite(sample, sizeX, sizeY, 0, 0);
		};
		Menu::Menu() {};
		void Menu::AddButton(Button* button) {
				buttons.push_back(button);
		};
		void Menu::SetLayer(Layer* layer) { privLayer = layer; };
		void Menu::Display(GLfloat alpha, GLfloat speed) {
			if (!set)
			{
				privLayer->push_abs_back(&menSprite);
				for (size_t i = 0; i < buttons.size(); i++)
					privLayer->push_abs_back(buttons.at(i)->GetSprite());
				set = true;
			}

			if (fadeIn)
			{
				menSprite.fade(alpha, speed);
				for (size_t i = 0; i < buttons.size(); i++)
					buttons.at(i)->GetSprite()->fade(1 , speed);
			}
		};
		void Menu::Hide(GLfloat speed) {
			menSprite.fade(0, speed);
			for (size_t i = 0; i < buttons.size(); i++)
				buttons.at(i)->GetSprite()->fade(0, speed);
		}
		void FadeSound(Sound* mySound, GLfloat fadeTime, GLfloat fadeValue) {
			audioQueue = menSprite.FadeIn(mySound, fadeTime, fadeValue);
		}
		void FadeSoundOut(GLfloat fadeTime, GLfloat fadeValue)
		{
			menSprite.FadeOut(audioQueue, fadeTime, fadeValue);
		}
		/// @brief Helper function to get the resolution of the screen
		/// @param width The width of the screen (passed by reference)
		/// @param height The height of the screen (passwed by reference)
		void Menu::getScreenResolution(int& width, int& height) {
			width = (GLint)GetSystemMetrics(SM_CXSCREEN);
			height = (GLint)GetSystemMetrics(SM_CYSCREEN);
		}
	private:
		GLboolean fadeIn = true;
		std::deque<Button*> buttons;
		Layer* privLayer = nullptr;
		Sprite menSprite;
		GLboolean set = false;
		GLint audioQueue;
};