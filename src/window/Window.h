#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Scene/Scene.h"
struct WindowConfig
{
	static WindowConfig default()
	{
		WindowConfig ret;
		ret.major_version = 4;
		ret.minor_version = 5;
		ret.width = 800;
		ret.height = 600;
		ret.window_title = "";
		ret.monitor = nullptr;
		ret.share = nullptr;
		return ret;
	}
	int major_version;
	int minor_version;
	size_t width;
	size_t height;
	std::string window_title;
	GLFWmonitor* monitor;
	GLFWwindow* share;
};

class Window
{
public:
	Window(const WindowConfig& config);
	~Window();

	 operator GLFWwindow*() { return window_; }
	 void render(Scene& scene);
	 bool shouldClose()
	 {
		 return glfwWindowShouldClose(window_);
	 }
	 const WindowConfig& getConfig()
	 {
		 return config_;
	 }
private:
	WindowConfig config_;
	GLFWwindow* window_;
	glm::mat4 projection;
	glm::mat4 view;
	//Camera main_camera_;
};

