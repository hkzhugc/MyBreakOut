#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "opengl_class/shader.h"
#include "opengl_class/VertexArray.h"
class ResourceManager
{
public:
	~ResourceManager();
	static void Clear();
	static Texture2D* GetTexture2D(const std::string & name);
	static Shader* GetShader(const std::string & name);
	static VertexArray* GetMesh(const std::string & name);
	static void AddMeshes(const std::string & name, VertexArray* mesh);
	static bool LoadShader(const std::string & name, const std::string& vs_path, const std::string& fs_path, const std::string& gs_path);
	static bool LoadTexture2D(const std::string & name, const std::string& texture_path, const bool image_vertical_flip = true);
private:
	ResourceManager() {}
	static ResourceManager& GetInstance();
	std::map<std::string, Texture2D*> Texture2Ds;
	std::map<std::string, Shader*> Shaders;
	std::map<std::string, VertexArray*> Meshes;
};

