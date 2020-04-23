#include "Window.h"
#include <iostream>
Window::Window(const WindowConfig& config)
	: config_(config)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.minor_version);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(config.width, config.height, config.window_title.c_str(), config.monitor, config.share);
	glfwMakeContextCurrent(window_);

	if (window_ == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// glfw function should be packed into Window class
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glDepthFunc(GL_LESS);

	// TODO : this is a 2D engine, so viewMat will be setted to Identity, projectionMat will be a othor projection
	view = glm::mat4(1.0);
	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
}

Window::~Window()
{
}

void clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::render(Scene & scene)
{
	// clear this window
	clear();
	scene.render(view, projection);
	glfwSwapBuffers(window_);
	glfwPollEvents();
}

