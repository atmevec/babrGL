#pragma once

#include "Sprite.h"
#include <iostream>
#include "Shader.h"
#include <deque>

#define GLEW_STATIC 1
#include <gl\glew.h>

#include <GL\GL.h>
#include <wtypes.h>
#include "stb_image_aug.h"

#define VERTS_NUM 54


class Layer
{
	public:
		Layer::Layer() {};
		Layer::Layer(GLint resourceID,
			GLfloat widthL,
			GLfloat heightL);
		~Layer();
		inline void push_back(Sprite* sprite) {
			added = true;
			sprites.push_back(sprite->setLayer(&texSizeX, &texSizeY, &LayerX, &LayerY));
		}
		inline void push_front(Sprite* sprite) {
			added = true;
			sprites.insert(sprites.begin(), sprite->setLayer(&texSizeX, &texSizeY, &LayerX, &LayerY));
		}
		inline void pop_back() {
			removed = true;
			sprites.pop_back();
		}
		inline void pop_front() {
			removed = true;
			sprites.erase(sprites.begin());
		}
		inline void insert(Sprite* sprite, GLint i)
		{
			sprites.insert(sprites.begin() + i, sprite->setLayer(&texSizeX, &texSizeY, &LayerX, &LayerY));
		}
		void Layer::push_back_batch(Sprite** sprite, GLint num);
		void Layer::push_front_batch(Sprite** sprite, GLint num);
		void Layer::push_abs_back(Sprite* sprite) {
			added = true;
			backSprites.push_back(sprite->setLayer(&texSizeX, &texSizeY, &LayerX, &LayerY));
			sprite->SetEngine(engine);
		};
		void Layer::push_abs_back_front(Sprite* sprite) {
			added = true;
			backSprites.push_front(sprite->setLayer(&texSizeX, &texSizeY, &LayerX, &LayerY));
			sprite->SetEngine(engine);
		};

		void Layer::pop_front_batch(GLint num);
		void Layer::pop_back_batch(GLint num);
		bool Layer::remove(Sprite* sprite);
		void Layer::clear() { sprites.clear(); backSprites.clear(); renderSprites.clear(); };
		inline void render() {
			Draw();
			glBindVertexArray(layerVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6 * (GLsizei) renderSprites.size());
			glBindVertexArray(0);
		}

		void Layer::SetEngine(SoLoud::Soloud* engine) { this->engine = engine; };

		void Layer::Draw();
		void Layer::simulate(GLfloat deltaT);
		GLfloat Layer::getX() { return LayerX; };
		GLfloat Layer::getY() { return LayerY; };
		void Layer::SetComplete() { completed = true; }
		GLboolean Layer::IsCompleted() { return completed; }
		GLboolean* Layer::GetCompletion() { return &completed; }

	private:
		GLboolean added = false, removed = false;
		GLfloat LayerX = 0, LayerY = 0;
		GLuint atlasTex = 0;
		std::deque<Sprite*> sprites;
		std::deque<Sprite*> backSprites;
		std::deque<Sprite*> renderSprites;
		GLuint swapVAO = 0, LayerVBO = 0, layerVAO = 0;
		GLfloat texSizeX = 0, texSizeY = 0, deltaT = 0;
		SoLoud::Soloud* engine = nullptr;
		GLboolean completed = false;
};