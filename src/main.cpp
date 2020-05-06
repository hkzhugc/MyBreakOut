#include <glad/glad.h>
#include <gl/GL.h>
#include "GLFW/glfw3.h"
#include <iostream>
#include "stb_image.h"
#include "Scene/Scene.h"
#include "Resources/ResourceManager.h"
#include "window/Window.h"
#include "Game.h"
#include "SpriteObject.h"
#include "GameLevel.h"
// need to implement some class

// init window config
Window window(WindowConfig::default());
Game gameManager(window.getConfig().width, window.getConfig().height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main(int argv, char** argc)
{
	// 1. init scene, including loading models(3d model, texture), build a structure to store and manage the scene
	// TODO :
	// Scene main_scene;
	// Source sources;
	// main_scene.initModel("name", "parent name");
	// sources.load_texture(); 
	// sources.load_Mesh(); 
	// main_scene.getModel("name").setMesh(sources.getMesh("name"));
	// main_scene.getModel("name").setTexture(sources.getTexture("name"), texture_type);
	// 2. init window, register a opengl window, managing the main camera, register the keybord and mouse events
	// TODO :
	// Window window; // init and set some default cofig and default register
	// window.config_viewport();
	// window.config_camera();
	// window.register_event();
	// 3. baked the cube map (including diffuse IBL conv and specular brdfLUT, prefilterMap) ? maybe also light probe?
	// TODO :
	// sources.load_cubeMap(); // if the cube map is a erpMap (theta phi), change it to a cube map to store it.
	// sources.get_cubeMap().bake(); // bake will produce three texture, diffuse_conv(), brdfLUT(), prefilterMap();
	// sources.get_cubeMap().diffuse_conv();
	// sources.get_cubeMap().brdfLUT();
	// sources.get_cubeMap().prefilterMap();
	// main_scene.addLightProbe(LightProbe(), "name");
	// main_scene.bakeLightProbe("name"); // bake will get a cubeMap, and diffuse_conv(), brdfLUT(), prefilterMap();
	// 4. starting render the scene
	// TODO ;
	// window.render(main_scene);

	// 4.21 : write a simple code about how to use DSA or some feature new in openGL 4.5
	// 4.22 : 
	//      1.change vertexArray class to DSA method
	//      2.implement Scene to manage object, ResourceManager to manage resources
	// 4.23 :
	//      1.

	glfwSetKeyCallback(window, key_callback);

	// load resouces
	ResourceManager::LoadShader("sprite", "../shader/2Dtexture.vs", "../shader/2Dtexture.fs", "");
	ResourceManager::LoadTexture2D("block", "../texture/block.png");
	ResourceManager::LoadTexture2D("solid-block", "../texture/solid-block.png");
	ResourceManager::LoadTexture2D("ball", "../texture/awesomeface.png");
	ResourceManager::AddDefaultMesh("sprite_quad", QUAD);

	// init game manager
	gameManager.init();
	// init a scene
	Scene scene;

	// set user defined object
	//auto level1 = new GameLevel();
	//size_t level_width = window.getConfig().width;
	//size_t level_height = window.getConfig().height / 2;
	//level1->loadLevel("../level/level1.txt", level_width, level_height);
	//level1->position = glm::vec2(0.f, window.getConfig().height  - level_height);
	//level1->ubo4ViewProject = window.getMatUbo(); // TODO : assign it when rendering?

	// add the object to the scene
	scene.addObeject("level", gameManager.level);
	scene.addObeject("player", gameManager.player);
	scene.addObeject("ball", gameManager.ball);
	
	// init the scene
	scene.init();
	float lastFrame = glfwGetTime();
	float currentFrame = glfwGetTime();
	float deltaTime;
	// run loop
	while (!window.shouldClose() && !gameManager.shouldExit())
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		gameManager.processInput();
		scene.update(deltaTime);
		gameManager.checkCollisions();
		window.render(scene);
	}

	// clear data
	ResourceManager::Clear();

	return 0;
}

// TODO : give a method to user define key_callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			gameManager.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			gameManager.Keys[key] = GL_FALSE;
	}
}