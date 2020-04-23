#pragma once
#include <vector>
#include "opengl_class/VertexArray.h"
#include "opengl_class/shader.h"
#include "Resources/Texture.h"
class SceneObeject
{
public:
	SceneObeject();
	virtual ~SceneObeject();

	virtual void init() = 0;
	virtual void render() = 0;

	glm::mat4 model;
	Texture2D* texture; // TODO : surport multi texture, for complex render
	VertexArray* mesh;
	Shader* shader;
	std::vector<SceneObeject*> childrens;
};

