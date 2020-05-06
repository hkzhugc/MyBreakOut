#pragma once
#include <vector>
#include <map>
#include "opengl_class/VertexArray.h"
#include "opengl_class/shader.h"
#include "Resources/Texture.h"

class Obeject
{
public:
	Obeject();
	virtual ~Obeject();

	virtual void init() = 0;
	virtual void render() = 0;
	virtual void update(float dt) = 0;
	glm::mat4 world();
	void bindTextures();

	bool isDestroyed;
	GLuint ubo4ViewProject;
	glm::mat4 model;
	std::map<std::string, Texture2D*> textures;
	VertexArray* mesh;
	Shader* shader;
	Obeject* parent;
	std::vector<Obeject*> childrens;
};

