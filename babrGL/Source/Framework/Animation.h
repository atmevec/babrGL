#pragma once

#include "Frame.h"
#include <list>

class Animation
{
	public:
		Animation::Animation() {};
		Animation::Animation(GLboolean loop, GLfloat frameTime);
		inline void addFrame(Frame frame) { frames.push_back(frame); };
		inline void Animation::disableLoop() { loop = false; }
		inline void Animation::clearAnimation() { frames.clear(); }
		Frame* getFrame();
		void cycleFrame();
		GLfloat getFrameTime() { return frameTime; };
		Frame getDefault() { return defaultFrame; };
		void setDefaultFrame(Frame defaultFrame) { this->defaultFrame = defaultFrame; };

	private:
		std::deque<Frame> frames;
		std::deque<Frame> frameCache;
		GLboolean loop = false;
		GLfloat timeAdjustment = 1, frameTime = 0;
		Frame defaultFrame;
};