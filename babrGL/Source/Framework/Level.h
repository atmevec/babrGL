#pragma once

#include "Layer.h"
#include "Menu.h"
#include <windows.h>

// GLFW
#include <GLFW/glfw3.h>

#include <functional>

class Level
{
public:
	// Default constructor
	Level::Level(GLint textureMap) {
		getScreenResolution(width, height);
		localLayer = Layer(textureMap, (GLfloat)width, (GLfloat)height);
		engine = new SoLoud::Soloud;
		engine->init();
		localLayer.SetEngine(engine);
	};

	Level::~Level()
	{
		engine->deinit();
	}

	// Setters

	/// @brief Utility to set the function that we use for keycallback during the duration of this level. CAN be rebound and re-adjusted, but for now this is intended to be one-call per level.
	/// @param keyCall The function that we want to call to handle input from the window.
	void Level::SetKeyCall(std::function<void(GLFWwindow*,GLint,GLint,GLint,GLint)> keyCall) { this->privateKeyCall = keyCall; };

	void Level::SetMouseCall(std::function<void(GLFWwindow*,GLint,GLint,GLint)>mouseCall) { this->privateMouseCall = mouseCall; };

			//void mouseProc(GLFWwindow* window, int button, int action, int mods)


		// Getters
		GLfloat Level::GetWidth() { return (GLfloat)width; };
		GLfloat Level::GetHeight() { return (GLfloat)height; };


		// Utilities

		/// @brief Utility function to draw and render the underlying layer/sprites
		void Level::Render();

		/// @brief Utility function to simulate the movement, animation, and sound of each sprite.
		/// @param dt The difference in time between now and the last time this simulate function was called.
		void Level::Simulate(GLfloat dt);

		/// @brief Function prototype that is called on each polled event with the program window
		/// @param window The window instance from GLFW
		/// @param key The key being pressed
		/// @param scancode The scancode for the pressed key
		/// @param action The action of the key being pressed (usually pressed/released)
		/// @param mode The mode of input.
		void Level::KeyCall(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode) { if (privateKeyCall != nullptr) privateKeyCall(window, key, scancode, action, mode); else { std::cout << "YOU NEED TO SET A KEYCALL FUNCTION"; } };
		
		void Level::MouseCall(GLFWwindow* window, GLint button, GLint action, GLint mods) { if(privateMouseCall != nullptr) privateMouseCall(window, button, action, mods); };

		/// @brief Utility to initiate anything in the Level we want to offload from declaration. CURRENTLY NOTHING IN HERE.
		/// @return Return this level so it can be added to the rendering pipeline of the Engine
		Level* Level::Load() { 
			return this;
		};

		/// @brief Utility to play a sound. Not used by sprites (they have their own function).
		/// @param mySound The sound which we would like to play.
		void Play(Sound* mySound) {
			engine->play(*(mySound->GetSound()));
		}

		void FadeIn(Sound* mySound, GLfloat fadeTime, GLfloat fadeValue) {
			GLint handle = engine->play(*(mySound->GetSound()), 0);
			engine->fadeVolume(handle, fadeValue, fadeTime);
		}

		/// @brief Utility function to add a sprite to the layer contained in a level. Puts sprite ON TOP of current render stack (visually) but back of deque.
		/// @param adder Sprite to be added to the level
		void Level::AddSprite(Sprite* adder) {
			localLayer.push_back(adder->SetEngine(engine));
		};

		/// @brief Helper function to return the local layer of this level
		/// @return Layer* localLayer = Pointer to local layer
		Layer* Level::GetLayer() {
			return &localLayer;
		}

		/// @brief Utility function to add a sprite to the layer contained in a level. Puts sprite ON BOTTOM of current render stack (visually) but front of deque.
		/// @param adder Sprite to be added to the level
		void Level::PushSprite_Front(Sprite* adder) { localLayer.push_front(adder->SetEngine(engine)); }

		void Level::AddMenu(Menu* menu) { menu->SetLayer(&localLayer); };

	private:
		Layer localLayer;
		std::function<void(GLFWwindow*,GLint,GLint,GLint,GLint)> privateKeyCall = nullptr;
		std::function<void(GLFWwindow*,GLint,GLint,GLint)> privateMouseCall = nullptr;
		void getScreenResolution(int& width, int& height);
		GLint width, height;
		SoLoud::Soloud* engine = nullptr;

};