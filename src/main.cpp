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

	// init window config
	Window window(WindowConfig::default());
	// init game manager
	Game gameManager(window.getConfig().width, window.getConfig().height);
	// init a scene
	Scene scene;

	// load resouces
	ResourceManager::LoadShader("sprite", "../shader/2Dtexture.vs", "../shader/2Dtexture.fs", "");
	ResourceManager::LoadTexture2D("block", "../texture/block.png");
	ResourceManager::LoadTexture2D("solid-block", "../texture/solid-block.png");
	ResourceManager::AddDefaultMesh("sprite_quad", QUAD);

	// set user defined object
	auto level1 = new GameLevel();
	size_t level_width = window.getConfig().width;
	size_t level_height = window.getConfig().height / 2;
	level1->loadLevel("../level/level1.txt", level_width, level_height);
	level1->position = glm::vec2(0.f, window.getConfig().height  - level_height);
	level1->ubo4ViewProject = window.getMatUbo(); // TODO : assign it when rendering?

	// add the object to the scene
	scene.addObeject("level1", level1);
	
	// init the scene
	scene.init();

	gameManager.init();

	// run loop
	while (!window.shouldClose() && !gameManager.shouldExit())
	{
		window.render(scene);
	}

	// clear data
	ResourceManager::Clear();

	return 0;
}