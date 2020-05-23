// Include header file
#include "Engine.h"

/// @brief Helper function to get the resolution of the screen
/// @param width The width of the screen (passed by reference)
/// @param height The height of the screen (passwed by reference)
void Engine::getScreenResolution(int& width, int& height) {
	width = (GLint)GetSystemMetrics(SM_CXSCREEN);
	height = (GLint)GetSystemMetrics(SM_CYSCREEN);
}

/// @brief The default constructor for the Engine class. Sets up a windowed fullscreen instance of the app.
/// @return 

Engine::Engine(GLint myMode /* = 0*/)
{
	this->MODE = myMode;
	initGLFW();
	initGlew();
	glViewport(0, 0, width, height);
	loadShaders();
}

/// @brief Function prototype that is called on each polled event with the program window
/// @param window The window instance from GLFW
/// @param key The key being pressed
/// @param scancode The scancode for the pressed key
/// @param action The action of the key being pressed (usually pressed/released)
/// @param mode The mode of input.
void key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);

void mouse_callback(GLFWwindow* window, GLint button, GLint action, GLint mods);

Level* passLevel;
/// @brief The constructor for the Engine which allows more customization of the class.
/// @param TITLE The title of the displayed Window
/// @param MODE The mode of the window. 0 is fullscreen, 1 fullscreen windowed, 3 is windowed
/// @param width The width of the displayed window
/// @param height The height of the displayed window
/// @param vsync Vsync on/off (this only works for fullscreen, all others use 0)
/// @return 
Engine::Engine(GLchar* TITLE, GLint MODE, GLint width, GLint height, GLint vsync )
{
	this->TITLE = TITLE;
	this->MODE = MODE;
	this->width = width;
	this->height = height;
	this->vsync = vsync;
	initGLFW();
	initGlew();
	glViewport(0, 0, width, height);
	loadShaders();
}

/// @brief The helper function for the Engine to initialize the GLEW backend
void Engine::initGlew()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/// @brief The helper function for the Engine to initialize the GLFW backend with the desired mode
void Engine::initGLFW()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4);

	getScreenResolution(width, height);
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	this->mode = *mode;

	switch (MODE)
	{
		case 0:
			window = glfwCreateWindow(width,
				height,
				TITLE,
				glfwGetPrimaryMonitor(),
				nullptr);
		break;
		case 1:
			window = glfwCreateWindow(mode->width,
				mode->height,
				TITLE,
				glfwGetPrimaryMonitor(),
				nullptr);
		break;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(vsync);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwGetWindowSize(window, &width, &height);
}

/// @brief Setting the Engine to display in a Windowed instance
/// @param width Width of the new windowed instance
/// @param height Height of the new windowed instance
void Engine::setWindowed(GLint width, GLint height)
{
	glfwDestroyWindow(window);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width,height,TITLE,nullptr,nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(vsync);
	glfwSetKeyCallback(window, key_callback);
}

/// @brief Set the Engine to fullscreen mode
void Engine::setFullScreen()
{
	glfwDestroyWindow(window);
	getScreenResolution(width, height);
	window = glfwCreateWindow(width,height,TITLE,glfwGetPrimaryMonitor(),nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(vsync);
	glfwSetKeyCallback(window, key_callback);
}

/// @brief Set the Engine to windowed mode
void Engine::setFullScreenWindowed()
{
	glfwDestroyWindow(window);
	glfwWindowHint(GLFW_RED_BITS, mode.redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode.greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode.blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode.refreshRate);
	window = glfwCreateWindow(mode.width,mode.height,TITLE,glfwGetPrimaryMonitor(),nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(vsync);
	glfwSetKeyCallback(window, key_callback);
}

/// @brief Load the level that will be being played next
/// @param activeLevel 
void Engine::LoadLevel(Level* activeLevel)
{
	this->activeLevel = activeLevel->Load();
	passLevel = this->activeLevel;
}

/// @brief Helper function to load and compile the shader program for displaying sprites.
void Engine::loadShaders()
{
	Shader shader;
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader.Use();
}

/// @brief Helper function that will simulate all sprites forward based on the passage of time
void Engine::simulate()
{
	std::chrono::time_point<std::chrono::system_clock> deltaT = time;
	time = std::chrono::system_clock::now();
	std::chrono::duration<GLfloat> difference = time - deltaT;
	GLfloat dt = difference.count() * EngineAdjustment;
	activeLevel->Simulate(dt);
}

/// @brief Function prototype that is called on each polled event with the program window
/// @param window The window instance from GLFW
/// @param key The key being pressed
/// @param scancode The scancode for the pressed key
/// @param action The action of the key being pressed (usually pressed/released)
/// @param mode The mode of input.
void key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode)
{
	passLevel->KeyCall(window, key, scancode, action, mode);
}


void mouse_callback(GLFWwindow* window, GLint button, GLint action, GLint mods)
{
	passLevel->MouseCall(window, button, action, mods);
}