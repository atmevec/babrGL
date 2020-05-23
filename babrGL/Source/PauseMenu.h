#pragma once
#include "Framework/Menu.h"

#define RESUMEX 700
#define RESUMEY 700
#define QUITX 1900
#define QUITY 700

class PauseMenu
{
	public:
		PauseMenu::PauseMenu(Layer* layer) {
			TextureSample pauseTextures(77, 77, 0, 94, 946);
			TextureSample resumeButton(278, 55, 0, 137, 276);
			TextureSample quitButton(278, 55, 0, 137, 164);
			privMenu = Menu(pauseTextures, layer);
			resume = new Button(resumeButton, 2, RESUMEX, RESUMEY);
			quit = new Button(quitButton, 2, QUITX, QUITY);
			privMenu.AddButton(resume);
			privMenu.AddButton(quit);
			privMenu.getScreenResolution(x, y);
		};
		PauseMenu::PauseMenu() {};
		Menu* PauseMenu::GetMenu() { return &privMenu; };
		void PauseMenu::Pause(GLFWwindow * window)
		{
			Reset();
			privMenu.Display(.8f, .5f);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			localPause = true;
		}
		void PauseMenu::Unpause(GLFWwindow* window)
		{
			privMenu.FadeSoundOut(.5f, 0);
			quit->Reset();
			resume->Reset();
			privMenu.Hide(.5f);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			Reset();
			localPause = false;
		}
		void PauseMenu::Press(GLFWwindow * window, GLdouble x, GLdouble y) {
			y = this->y - y;
			if (localPause)
			{
				if (resume->Press(x, y))
				{
					resume->SetTexture(137, 330);
				}
				else if (quit->Press(x, y))
				{
					quit->SetTexture(137, 219);
				}
			}
		};
		void PauseMenu::Release(GLFWwindow* window, GLdouble x, GLdouble y, GLboolean& paused) {
			y = this->y - y;
			if (localPause)
			{
				if (quit->Release(x, y))
				{
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
				else if (resume->Release(x, y))
				{
					paused = false;
					Unpause(window);
				}
				else
					Reset();
			}
		};
		void PauseMenu::Reset()
		{
			quit->GetSprite()->setTexOffset(137,164);
			resume->GetSprite()->setTexOffset(137, 276);
		}
	private:
		Menu privMenu;
		Button* resume = nullptr;
		Button* quit = nullptr;
		GLint y = 0, x = 0;
		Frame Frame1, Frame2;
		GLboolean localPause = false;
};