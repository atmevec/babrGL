#include "Layer.h"


#define SPRITE_SIZE 54

Layer::Layer(GLint resourceID, GLfloat widthL, GLfloat heightL)
{
	glGenTextures(1, &atlasTex);

	glBindTexture(GL_TEXTURE_2D, atlasTex);

	GLint width, height;
	GLint RGBA = 4;

	HRSRC imageRes = NULL;
	HGLOBAL imageResDataHandle = NULL;
	
	HMODULE hModule = GetModuleHandle(NULL);
	
	HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(resourceID), L"PNG");
	HGLOBAL hMemory = LoadResource(hModule, hResource);
	DWORD dwSize = SizeofResource(hModule, hResource);
	LPVOID lpAddress = LockResource(hMemory);
	stbi_uc* image = new stbi_uc[dwSize];
	memcpy(image, lpAddress, dwSize);

	GLubyte* imageLoad = stbi_load_from_memory(image, dwSize, &width, &height, 0, RGBA);
	
	UnlockResource(hMemory);

	delete[] image;
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageLoad);
	glGenerateMipmap(GL_TEXTURE_2D);

	free((void*)imageLoad);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	LayerX = widthL;
	LayerY = heightL;
	this->texSizeX = (GLfloat) width;
	this->texSizeY = (GLfloat) height;
}

Layer::~Layer()
{
	if (&atlasTex != nullptr)
		glDeleteTextures(0, &atlasTex);

	if (&LayerVBO != nullptr)
		glDeleteBuffers(1, &LayerVBO);

	if (&swapVAO != nullptr)
		glDeleteVertexArrays(1, &swapVAO);

	if (&layerVAO != nullptr)
		glDeleteVertexArrays(1, &layerVAO);
}

void Layer::push_back_batch(Sprite** sprite, GLint num)
{
	added = true;
	for (GLint i = 0; i < num; i++)
	{
		sprites.push_back(sprite[i]->setLayer(&texSizeX, &texSizeY, &LayerX, &LayerY));
	}
}

void Layer::push_front_batch(Sprite ** sprite, GLint num)
{
	added = true;
	for (GLint i = num; i > 0; i--)
	{
		sprites.insert(sprites.begin(), sprite[i]->setLayer(&texSizeX, &texSizeY, &LayerX, &LayerY));
	}
}

void Layer::pop_front_batch(GLint num)
{
	removed = true;
	for (GLint i = 0; i < num; i++)
	{
		sprites.erase(sprites.begin());
	}
}

void Layer::pop_back_batch(GLint num)
{
	removed = true;
	for (GLint i = 0; i < num; i++)
	{
		sprites.pop_back();
	}
}

bool Layer::remove(Sprite* sprite)
{
	bool run = true;
	for (size_t i = 0; i < sprites.size(); i++)
	{
		if (sprites[i] == sprite)
		{
			sprites.erase(sprites.begin() + i);
			removed = true;
			return true;
		}
	}
	return false;
}

void Layer::simulate(GLfloat deltaT)
{
	std::for_each(renderSprites.begin(), renderSprites.end(),
		[deltaT](Sprite* sprite)
		{
			sprite->simulate(deltaT);
		});
}

void Layer::Draw()
{
	if (added || removed)
	{
		added = false;
		removed = false;
		renderSprites.clear();
		for (int i = 0; i < sprites.size(); i++)
		{
			renderSprites.push_back(sprites[i]);
		}
		for (int i = 0; i < backSprites.size(); i++)
		{
			renderSprites.push_back(backSprites[i]);
		}
		glBindVertexArray(swapVAO);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &LayerVBO);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &swapVAO);

		glGenVertexArrays(1, &swapVAO);
		glGenBuffers(1, &LayerVBO);
		glBindVertexArray(swapVAO);
		glBindBuffer(GL_ARRAY_BUFFER, LayerVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * VERTS_NUM * renderSprites.size(), NULL, GL_DYNAMIC_DRAW);

		for (size_t i = 0; i < renderSprites.size(); i++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, (i * (sizeof(GLfloat) * VERTS_NUM)), sizeof(GLfloat) * VERTS_NUM, renderSprites[i]->Print());
		}
		glBindBuffer(GL_ARRAY_BUFFER, LayerVBO);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERT_SIZE * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERT_SIZE * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERT_SIZE * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VERT_SIZE * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		layerVAO = swapVAO;
	}
	else
	{
		glBindVertexArray(swapVAO);
		glBindBuffer(GL_ARRAY_BUFFER, LayerVBO);

		for (size_t i = 0; i < renderSprites.size(); i++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, (i * (sizeof(GLfloat) * VERTS_NUM)), sizeof(GLfloat) * VERTS_NUM, renderSprites[i]->Print());
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		layerVAO = swapVAO;
	}
}
