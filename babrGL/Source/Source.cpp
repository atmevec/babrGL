// GL includes
#include "Framework/Engine.h"
#include "Level1.h"
#include <iostream>

int main()
{
	Engine testEngine(1);
	Level1 myLevel;

	testEngine.LoadLevel(myLevel.LoadLevel());

	testEngine.setBGColor(1, 1, 1);

	while (!glfwWindowShouldClose(testEngine.getWindow()))
	{
		// Poll for events on the primary window
		glfwPollEvents();

		// Simulate movement
		testEngine.simulate();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Put our drawn changes into the display buffer
		testEngine.render();

		// Display the new items to the screen
		glfwSwapBuffers(testEngine.getWindow());
	}

	testEngine.Close();
	return 0;
}