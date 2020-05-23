#include "Level.h"

void Level::Render()
{
	localLayer.render();
}

/// @brief Helper function that will simulate all sprites forward based on the passage of time
void Level::Simulate(GLfloat dt)
{
	localLayer.simulate(dt);
}

/// @brief Helper function to get the resolution of the screen
/// @param width The width of the screen (passed by reference)
/// @param height The height of the screen (passwed by reference)
void Level::getScreenResolution(int& width, int& height) {
	width = (GLint)GetSystemMetrics(SM_CXSCREEN);
	height = (GLint)GetSystemMetrics(SM_CYSCREEN);
}