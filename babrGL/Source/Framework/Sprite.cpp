#include "Sprite.h"

Sprite::Sprite(
	TextureSample sample,
	GLfloat scale,
	GLfloat posX,
	GLfloat posY)
{

	velocityX = 0;
	velocityY = 0;
	glOffsetX = sample.GetOffsetX();
	glOffsetY = sample.GetOffsetY();
	defStateX = glOffsetX;
	defStateY = glOffsetY;
	glSizeTexX = sample.GetSizeX();
	glSizeTexY = sample.GetSizeY();

	X = posX * 2;
	Y = posY * 2;
	fadeValue = sample.GetAlpha();
	this->alpha = sample.GetAlpha();
	this->sizeX = sample.GetSizeX() * scale;
	this->sizeY = sample.GetSizeY() * scale;

	zoomULimitX = upperZoomBound * sizeX;
	zoomLLimitX = lowerZoomBound * sizeX;

	zoomULimitY = upperZoomBound * sizeY;
	zoomLLimitY = lowerZoomBound * sizeY;
}

Sprite::Sprite(TextureSample sample, GLfloat sizeX, GLfloat sizeY, GLfloat posX, GLfloat posY)
{
	velocityX = 0;
	velocityY = 0;
	glOffsetX = sample.GetOffsetX();
	glOffsetY = sample.GetOffsetY();
	defStateX = glOffsetX;
	defStateY = glOffsetY;
	glSizeTexX = sample.GetSizeX();
	glSizeTexY = sample.GetSizeY();

	X = posX * 2;
	Y = posY * 2;
	fadeValue = sample.GetAlpha();
	this->alpha = sample.GetAlpha();
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	zoomULimitX = upperZoomBound * sizeX;
	zoomLLimitX = lowerZoomBound * sizeX;

	zoomULimitY = upperZoomBound * sizeY;
	zoomLLimitY = lowerZoomBound * sizeY;
}

Sprite::Sprite(
	TextureSample sample,
	GLfloat posX,
	GLfloat posY)
{
	velocityX = 0;
	velocityY = 0;
	glOffsetX = sample.GetOffsetX();
	glOffsetY = sample.GetOffsetY();
	defStateX = glOffsetX;
	defStateY = glOffsetY;
	this->glSizeTexX = sample.GetSizeX();
	this->glSizeTexY = sample.GetSizeY();

	X = posX * 2;
	Y = posY * 2;
	fadeValue = sample.GetAlpha();
	alpha = sample.GetAlpha();
	sizeX = sample.GetSizeX();
	sizeY = sample.GetSizeY();

	zoomULimitX = upperZoomBound * sizeX;
	zoomLLimitX = lowerZoomBound * sizeX;

	zoomULimitY = upperZoomBound * sizeY;
	zoomLLimitY = lowerZoomBound * sizeY;
}



Sprite::~Sprite()
{
	if (PrivSprite)
		delete PrivSprite;
}

void Sprite::setTexOffset(GLfloat offsetX, GLfloat offsetY)
{
	if (layerTexX != nullptr)
	{
		glOffsetX = offsetX / *layerTexX;
		glOffsetY = offsetY / *layerTexY;

		PrivSprite[4] = glOffsetX;
		PrivSprite[5] = glOffsetY;
		PrivSprite[13] = glOffsetX;
		PrivSprite[14] = glOffsetY;
		PrivSprite[22] = glOffsetX;
		PrivSprite[23] = glOffsetY;
		PrivSprite[31] = glOffsetX;
		PrivSprite[32] = glOffsetY;
		PrivSprite[40] = glOffsetX;
		PrivSprite[41] = glOffsetY;
		PrivSprite[49] = glOffsetX;
		PrivSprite[50] = glOffsetY;
	}
	else
	{
		std::cout << "Warning: Sprite referenced/animated with no layer." << std::endl;
	}
}

void Sprite::setSize(GLfloat newX, GLfloat newY)
{
	X += (sizeX - newX) / 2;
	Y += (sizeY - newY) / 2;
	sizeX = newX;
	sizeY = newY;


	// 1.0
	PrivSprite[0] = (-1 + (X / *layerX));
	PrivSprite[1] = (-1 + (Y / *layerY));

	// 1.1
	PrivSprite[9] = (-1 + (X / *layerX));
	PrivSprite[10] = (-1 + (Y / *layerY) + (sizeY * 2 / *layerY));

	//1.2
	PrivSprite[18] = (-1 + (X / *layerX) + (sizeX * 2 / *layerX));
	PrivSprite[19] = (-1 + (Y / *layerY));

	// 2.0
	PrivSprite[27] = (-1 + (X / *layerX));
	PrivSprite[28] = (-1 + (Y / *layerY) + (sizeY * 2 / *layerY));

	// 2.1
	PrivSprite[36] = (-1 + (X / *layerX) + (sizeX * 2 / *layerX));
	PrivSprite[37] = (-1 + (Y / *layerY) + (sizeY * 2 / *layerY));

	// 2.2
	PrivSprite[45] = (-1 + (X / *layerX) + (sizeX * 2 / *layerX));
	PrivSprite[46] = (-1 + (Y / *layerY));
}

void Sprite::zoomIn()
{
	if (sizeX * zoomSpeed < zoomULimitX && sizeY * zoomSpeed < zoomULimitY)
		setSize(sizeX*zoomSpeed, sizeY*zoomSpeed);
}

void Sprite::zoomOut()
{
	if (sizeY * zoomSpeed > zoomLLimitY && sizeX * zoomSpeed > zoomLLimitX)
		setSize(sizeX / zoomSpeed, sizeY / zoomSpeed);
}

Sprite* Sprite::setLayer(GLfloat* layerTexX, GLfloat* layerTexY, GLfloat* layerX, GLfloat* layerY)
{
	this->layerTexX = layerTexX;
	this->layerTexY = layerTexY;
	this->layerX = layerX;
	this->layerY = layerY;
	glOffsetX = glOffsetX / *layerTexX;
	glOffsetY = glOffsetY / *layerTexY;
	glSizeTexX = glSizeTexX / *layerTexX;
	glSizeTexY = glSizeTexY / *layerTexY;
	PrivSprite = new GLfloat[VERTS_NUM]
	{
		-1 + ((X / *layerX) * 2), -1 + (Y / *layerY),
		0.0f, 1.0f,
		glOffsetX, glOffsetY,
		glSizeTexX, glSizeTexY, alpha,

		-1 + ((X / *layerX) * 2), -1 + (Y / *layerY) + (sizeY * 2 / *layerY),
		0.0f, 0.0f,
		glOffsetX, glOffsetY,
		glSizeTexX, glSizeTexY, alpha,

		-1 + ((X / *layerX) * 2) + (sizeX * 2 / *layerX),  -1 + (Y / *layerY),
		1.0f, 1.0f,
		glOffsetX, glOffsetY,
		glSizeTexX, glSizeTexY, alpha,

		-1 + ((X / *layerX) * 2), -1 + (Y / *layerY) + (sizeY * 2 / *layerY),
		0.0f, 0.0f,
		glOffsetX, glOffsetY,
		glSizeTexX, glSizeTexY, alpha,

		-1 + ((X / *layerX) * 2) + (sizeX * 2 / *layerX),  -1 + (Y / *layerY) + (sizeY * 2 / *layerY),
		1.0f, 0.0f,
		glOffsetX, glOffsetY,
		glSizeTexX, glSizeTexY, alpha,

		-1 + ((X / *layerX) * 2) + (sizeX * 2 / *layerX),  -1 + (Y / *layerY),
		1.0f, 1.0f,
		glOffsetX, glOffsetY,
		glSizeTexX, glSizeTexY, alpha
	};

	return this;
}

void Sprite::teleport(GLfloat newX, GLfloat newY)
{
	X += (newX);
	Y += (newY);

	// 1.0
	PrivSprite[0] = (-1 + (X / *layerX));
	PrivSprite[1] += (newY / *layerY);

	// 1.1
	PrivSprite[9] = (-1 + (X / *layerX));
	PrivSprite[10] += newY / *layerY;

	//1.2
	PrivSprite[18] = (-1 + (X / *layerX) + (sizeX * 2 / *layerX));
	PrivSprite[19] += newY / *layerY;

	// 2.0
	PrivSprite[27] = (-1 + (X / *layerX));
	PrivSprite[28] += newY / *layerY;

	// 2.1
	PrivSprite[36] = (-1 + (X / *layerX) + (sizeX * 2 / *layerX));
	PrivSprite[37] += newY / *layerY;

	// 2.2
	PrivSprite[45] = (-1 + (X / *layerX) + (sizeX * 2 / *layerX));
	PrivSprite[46] += newY / *layerY;
}

inline void Sprite::setAlpha(GLfloat alpha)
{
	this->alpha = alpha;
	PrivSprite[8] = alpha;
	PrivSprite[17] = alpha;
	PrivSprite[26] = alpha;
	PrivSprite[35] = alpha;
	PrivSprite[44] = alpha;
	PrivSprite[53] = alpha;
}

void Sprite::simulate(GLfloat deltaT)
{
	if (spriteAnimation != nullptr)
	{
		if (spriteAnimation->getFrame() != nullptr)
		{
			if (accumulator >= spriteAnimation->getFrameTime())
			{
				setTexOffset(spriteAnimation->getFrame()->getX(), spriteAnimation->getFrame()->getY());
				if (spriteAnimation->getFrame()->getSound() != nullptr)
					Play(spriteAnimation->getFrame()->getSound());
				spriteAnimation->cycleFrame();
				accumulator = 0;
			}
			else
			{
				accumulator += deltaT;
			}
		}
		else
			stopAnimation();
	}

	if (fadeValue != alpha)
	{
		if ((alpha + fadeStep > fadeValue && alpha - fadeStep < fadeValue))
		{
			setAlpha(fadeValue);
		}
		else
		{
			if (fAccumulator >= fadeSpeed)
			{
				if (fadeValue > alpha)
				{
					setAlpha(alpha + fadeStep);
					fAccumulator = 0;
				}
				else
				{
					setAlpha(alpha - fadeStep);
					fAccumulator = 0;
				}
			}
			else
				fAccumulator += deltaT;
		}
	}
	deltaX = velocityX * deltaT;
	deltaY = velocityY * deltaT;
	if (bounded)
	{
		if (deltaX + X < xMax && deltaX + X > xMin)
		{
			if (deltaY + Y < yMax && deltaY + Y > yMin)
				teleport(deltaX, deltaY);
			else
				teleport(deltaX, 0);
		}
		else if (deltaY + Y < yMax && deltaY + Y > yMin)
		{
			teleport(0, deltaY);
		}
	}
	else
		teleport(deltaX, deltaY);
}

void Sprite::animate(Animation* animate)
{
	if (spriteAnimation == nullptr)
	{
		spriteAnimation = animate;
		defStateX = animate->getDefault().getX();
		defStateY = animate->getDefault().getY();
		accumulator = 10000000;
	}
	else
	{
		swapAnimation = animate;
		setTexOffset(defStateX, defStateY);
		stopAnimation();
	}
}

void Sprite::stopAnimation()
{
	spriteAnimation = nullptr;
	setTexOffset(defStateX, defStateY);
	if (swapAnimation != nullptr)
	{
		animate(swapAnimation);
		swapAnimation = nullptr;
	}
}

void Sprite::print()
{
	std::cout << "1.0: " << PrivSprite[1] << std::endl
		<< "1.1: " << PrivSprite[10] << std::endl
		<< "1.2: " << PrivSprite[19] << std::endl
		<< "2.0: " << PrivSprite[28] << std::endl
		<< "2.1: " << PrivSprite[37] << std::endl
		<< "2.2: " << PrivSprite[46] << std::endl << std::endl <<
		"Diff: " << PrivSprite[1] - PrivSprite[19] << std::endl << std::endl;
}

void Sprite::setDefState(GLfloat defStateX, GLfloat defStateY)
{
	this->defStateX = defStateX;
	this->defStateY = defStateY;
}
