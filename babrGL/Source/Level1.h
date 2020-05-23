#pragma once

#include "Framework/Level.h"
#include "Alex.h"
#include "resource1.h"
#include "PauseMenu.h"
#include "Pudge.h"

class Level1
{
	public:
		Level1::Level1();
		Level* Level1::LoadLevel() { 
			return &privLevel;
		};
	private:
		Level privLevel = Level(TEXTURE_MAP);
};