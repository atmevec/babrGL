#pragma once

#include <deque>
#include <GL\glew.h>
#include "Sound.h"

class Frame
{
	public:
		Frame::Frame(GLfloat offsetX, GLfloat offsetY) {
			this->offsetX = offsetX;
			this->offsetY = offsetY;
		};
		Frame::Frame() {};
		
		// Getters

		inline GLfloat getX() { return offsetX; };
		inline GLfloat getY() { return offsetY; };
		inline GLboolean hasSound() {
			if (sound != nullptr)
				return true;
			else
				return false;
		}
		inline Sound* getSound() { return sound; };


		// Setters

		inline void setX(GLfloat X) { offsetX = X; };
		inline void setY(GLfloat Y) { offsetX = Y; };
		inline void setSound(Sound* sound) { this->sound = sound; }

	private:
		GLfloat offsetX = 0, offsetY = 0;
		Sound* sound = nullptr;
};