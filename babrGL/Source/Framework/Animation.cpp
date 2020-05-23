#include "Animation.h"

Animation::Animation(GLboolean loop, GLfloat frameTime)
{
	this->loop = loop;
	this->frameTime = frameTime * timeAdjustment;
}

Frame* Animation::getFrame()
{
	if (!frames.empty())
	{
		return &frames.front();
	}
	else
	{
		frames = frameCache;
		return nullptr;
	}
}

void Animation::cycleFrame()
{
	if (loop)
	{
		frames.push_back(frames.front());
	}
	else
	{
		frameCache.push_back(frames.front());
	}
	frames.pop_front();
}