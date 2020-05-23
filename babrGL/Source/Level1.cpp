#include "Level1.h"

void keyProc(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
void mouseProc(GLFWwindow* window, int button, int action, int mods);

GLboolean A = false, D = false;
Pudge alex1;
GLboolean paused = false;
PauseMenu pauseMenu;
Sound menuSound = Sound(SOUND_JAZZ);
GLdouble x, y;
Level* localLevel;

void loadLevel()
{
	localLevel->SetKeyCall(keyProc);
	localLevel->SetMouseCall(mouseProc);
	pauseMenu = PauseMenu(localLevel->GetLayer());
	localLevel->AddSprite(alex1.getSprite());
}

Level1::Level1()
{
	localLevel = &privLevel;
	loadLevel();
}

void mouseProc(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		// THIS IS FROM TOP LEFT BUT LAYER COUNTS FROM BOTTOM LEFT--YOU NEED TO INVERT THESE VALUES
		glfwGetCursorPos(window, &x, &y);
		pauseMenu.Press(window, x, y);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		// THIS IS FROM TOP LEFT BUT LAYER COUNTS FROM BOTTOM LEFT--YOU NEED TO INVERT THESE VALUES
		glfwGetCursorPos(window, &x, &y);
		pauseMenu.Release(window, x, y, paused);
	}
}

void keyProc (GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint modey)
{
	switch (action)
	{
	case GLFW_PRESS:
		if (!paused)
		{
			//alex.Press(key);
			alex1.Press(key);
		}

		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			paused = !paused;
			if (paused)
			{
				pauseMenu.Pause(window);
				pauseMenu.GetMenu()->FadeSound(&menuSound, .5f, 10);
				alex1.Stop();
			}
			else
			{
				pauseMenu.Unpause(window);
				pauseMenu.GetMenu()->FadeSoundOut(.5f, 0);
			}

			break;
		case GLFW_KEY_SPACE:
			//glfwSetWindowShouldClose(window, GL_TRUE);
			//alex.getSprite()->fade(0, 0.01f, .2f);
			break;
		}
		break;
	case GLFW_RELEASE:
		if (!paused)
		{
			//alex.Release(key);
			alex1.Release(key);
		}
		break;
	}
}