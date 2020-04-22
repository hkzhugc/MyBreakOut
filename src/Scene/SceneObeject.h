#pragma once
#include <vector>
#include "opengl_class/VertexArray.h"
#include "opengl_class/shader.h"
#include "Resources/Texture.h"
class SceneObeject
{
public:
	SceneObeject();
	~SceneObeject();

	glm::mat4 model_mat;
	Texture2D* texture; // TODO : surport multi texture, for complex render
	VertexArray* mesh;
	Shader* shader;
	std::vector<SceneObeject*> childrens;
};

