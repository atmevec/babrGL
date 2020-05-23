#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <iostream>
#include <algorithm>
#include <deque>
#include "Animation.h"
#include "Sound.h"
#include "TextureSample.h"

#define VERTS_NUM 54
#define POS_DATA 12
#define TEX_DATA 12
#define UV_DATA 12
#define VZOOM_DATA 18
#define VERT_SIZE 9

class Sprite
{
	public:
		/// @brief Default sprite constructor to allow for dynamically-designed sprites
		/// @return 
		Sprite::Sprite() {};

		/// @brief A sprite is the basic container for vertice data
		/// @param sample A TextureSample which contains information about the sprite's texture
		/// @param scale A value to scale the sprite's size by (eg 2 times the size of the texturemap sample)
		/// @param posX The X position of the sprite
		/// @param posY The Y position of the sprite
		/// @return 
		Sprite::Sprite(
			TextureSample sample,
			GLfloat scale,
			GLfloat posX,
			GLfloat posY );

		/// @brief A sprite is the basic container for vertice data
		/// @param sample A TextureSample which contains information about the sprite's texture
		/// @param sizeX The size of the sprite in the X dimension (can be used to scale a sprite's image)
		/// @param sizeY The size of the sprite in the Y dimension (can be used to scale a sprite's image)
		/// @param posX The X position of the sprite
		/// @param posY The Y position of the sprite
		/// @return 
		Sprite::Sprite(
			TextureSample sample,
			GLfloat sizeX,
			GLfloat sizeY,
			GLfloat posX,
			GLfloat posY);

		/// @brief A sprite is the basic container for vertice data
		/// @param sample A TextureSample which contains information about the sprite's texture
		/// @param posX The X position of the sprite
		/// @param posY The Y position of the sprite
		/// @return 
		Sprite::Sprite(
			TextureSample sample,
			GLfloat posX,
			GLfloat posY );
		~Sprite();

		// Getters
		inline GLfloat getX() { return X; }
		inline GLfloat getY() { return Y; }
		inline GLfloat getAlpha() { return alpha; }
		inline GLfloat getVelocityX() { return velocityX; }
		inline GLfloat getVelocityY() { return velocityY; }


		// Setters
		void setTexOffset(GLfloat offsetX, GLfloat offsetY);
		void teleport(GLfloat x, GLfloat y);
		inline void setAlpha(GLfloat alpha);
		void simulate(GLfloat deltaT);
		inline void setVelocity(GLfloat velX, GLfloat velY) { velocityX += velX; velocityY += velY; };
		void animate(Animation* animate);
		void stopAnimation();
		void print();
		void setDefState(GLfloat defStateX, GLfloat defStateY);
		void Sprite::fade(GLfloat fade, GLfloat speed) { this->fadeValue = fade; fadeStep = (GLfloat)(.05 / pow(2, ((speed * 2) - 1))); this->fadeSpeed = .001f; };
		Sprite* Sprite::SetEngine(SoLoud::Soloud* engine) { this->engine = engine; return this; };
		Sprite* setLayer(GLfloat* layerTexX, GLfloat* layerTexY, GLfloat* layerX, GLfloat* layerY);
		GLfloat* Sprite::Print() { return PrivSprite; };
		void Play(Sound* mySound) {
			engine->play(*(mySound->GetSound()));
		}
		GLint FadeIn(Sound* mySound, GLfloat fadeTime, GLfloat fadeValue) {
			GLint handle = engine->play(*(mySound->GetSound()), 0);
			engine->fadeVolume(handle, fadeValue, fadeTime);
			return handle;
		}
		void FadeOut(GLint handle, GLfloat fadeTime, GLfloat fadeValue) {
			engine->fadeVolume(handle, fadeValue, fadeTime);
			engine->scheduleStop(handle, fadeTime);
		}
		void FadeVol(GLint handle, GLfloat fadeTime, GLfloat fadeValue) {
			engine->fadeVolume(handle, fadeValue, fadeTime);
		}
		void Stop()
		{
			velocityX = 0;
			velocityY = 0;
			stopAnimation();
		}
		void SetBounds(GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin)
		{
			bounded = true;
			this->xMax = (xMax * 2) - (sizeX * 2);
			this->xMin = xMin;
			this->yMax = (yMax * 2) - (sizeY * 1.5f);
			this->yMin = yMin;
		}

	private:
	GLfloat* PrivSprite = nullptr;
	GLfloat X = 0, Y = 0,
		alpha = 1, texX = 0, texY = 0,
		sizeX = 0, sizeY = 0,
		zoomULimitX = 0, zoomULimitY = 0,
		zoomLLimitX = 0, zoomLLimitY = 0,
		glOffsetX = 0, glOffsetY = 0,
		glSizeTexX = 0, glSizeTexY = 0;
	GLfloat *layerTexX = nullptr,*layerTexY = nullptr, *layerX = nullptr, *layerY = nullptr;
	GLfloat lowerZoomBound = 0.4f;
	GLfloat upperZoomBound = 3.0f;
	GLfloat zoomSpeed = 1.17f;
	GLfloat velocityX = 0, velocityY = 0;
	Animation* spriteAnimation = nullptr,* swapAnimation = nullptr;
	GLboolean loop = false;
	GLint frame = 0;
	GLfloat accumulator = 0, fAccumulator = 0;
	GLfloat defStateX = 0, defStateY = 0, fadeValue = 1, fadeStep = 1, fadeSpeed = 16;
	SoLoud::Soloud* engine = nullptr;
	GLboolean bounded = false;
	GLfloat xMax, xMin, yMax, yMin, deltaX, deltaY;
	// Setters
	void setSize(GLfloat x, GLfloat y);
	void zoomIn();
	void zoomOut();
};
