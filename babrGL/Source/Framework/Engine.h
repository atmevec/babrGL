#pragma once

#include <windows.h>

// Type inclusions
#include <deque>

#define GLEW_STATIC 1
// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Level.h"

// GLM Mathemtics
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Time for math testing
#include <chrono>
#include <algorithm>

class Engine
{
public:

	// Constructors
	Engine::Engine(GLint myMode = 0);
	Engine::Engine(GLchar* TITLE, GLint MODE, GLint width, GLint height, GLint vsync);

	// Setters
	void setWindowed(GLint width, GLint height);
	void setFullScreen();
	void setFullScreenWindowed();
	void LoadLevel(Level* activeLevel);

	// Utilities
	void render() { if (activeLevel != nullptr) activeLevel->Render();	};
	void simulate();
	void setBGColor(GLfloat R, GLfloat G, GLfloat B) { glClearColor(R, G, B, 1.0f); };

	void Close()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void ShowCursor() {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void HideCursor() {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	// Getters
	inline GLfloat getWidth() { return (GLfloat)width; };
	inline GLfloat getHeight() { return (GLfloat)height; };
	GLFWwindow* getWindow() { return window; };

private:
	void initGlew();
	void initGLFW();
	void loadShaders();
	GLFWwindow* window;
	GLchar* TITLE = "DEFAULT TITLE";
	GLint MODE, width, height, vsync = 1;
	void getScreenResolution(int& width, int& height);
	std::chrono::time_point<std::chrono::system_clock> time;
	GLfloat EngineAdjustment = 100;
	Level* activeLevel = nullptr;
	GLFWvidmode mode;
};