#pragma once

class TextureSample
{

public:
	TextureSample::TextureSample(GLfloat sizeX, GLfloat sizeY, GLfloat alpha, GLfloat offsetX, GLfloat offsetY) { 
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->alpha = alpha;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
	};

	GLfloat GetSizeX() { return sizeX; }
	GLfloat GetSizeY() { return sizeY; }
	GLfloat GetAlpha() { return alpha; }
	GLfloat GetOffsetX() { return offsetX; }
	GLfloat GetOffsetY() { return offsetY; }

private:
	GLfloat sizeX, sizeY, alpha, offsetX, offsetY;
};