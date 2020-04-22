#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include "Scene/Scene.h"
#include "Resources/ResourceManager.h"
#include "window/Window.h"
#include "Game.h"
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

	// init window config
	Window window(WindowConfig::default());
	Scene scene;
	// load resouces
	ResourceManager::LoadShader("tex", "../shader/screen.vs", "../shader/ssaoBlur.fs", "");
	ResourceManager::LoadTexture2D("tex", "../texture/mario.png");
	
	// init VAO
	VertexArray quadVAO;
	quadVAO.initAsQuad();
	ResourceManager::AddMeshes("quad", &quadVAO); // TODO : resources managed should belong to ResourceManager
	scene.addObeject("screen", new SceneObeject());
	scene.getObject("screen").mesh = ResourceManager::GetMesh("quad");
	scene.getObject("screen").model_mat = glm::mat4(1.0);
	scene.getObject("screen").shader = ResourceManager::GetShader("tex");
	scene.getObject("screen").texture = ResourceManager::GetTexture2D("tex");

	Game gameManager(window.getConfig().width, window.getConfig().height);

	while (!window.shouldClose() && !gameManager.shouldExit())
	{
		window.render(scene);
	}
	ResourceManager::Clear();
	return 0;
}