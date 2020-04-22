#include <fstream>
#include <sstream>
#include <iostream>
#include "ResourceManager.h"

using namespace std;
ResourceManager::~ResourceManager()
{
	for (auto iter : Shaders)
	{
		delete iter.second;
	}
	Shaders.clear();
	for (auto iter : Texture2Ds)
	{
		delete iter.second;
	}
	Texture2Ds.clear();
}

ResourceManager & ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;
}

Shader * ResourceManager::GetShader(const std::string & name)
{
	// TODO: if shaders[name] dosent exist
	auto& manager = GetInstance();
	return manager.Shaders[name];
}

VertexArray * ResourceManager::GetMesh(const std::string & name)
{
	// TODO: if Meshes[name] dosent exist
	auto& manager = GetInstance();
	return manager.Meshes[name];
}

void ResourceManager::Clear()
{
	auto& manager = GetInstance();
	for (auto iter : manager.Shaders)
	{
		delete iter.second;
	}
	manager.Shaders.clear();
	for (auto iter : manager.Texture2Ds)
	{
		delete iter.second;
	}
	manager.Texture2Ds.clear();
}

void ResourceManager::AddMeshes(const std::string & name, VertexArray * mesh)
{
	auto& manager = GetInstance();
	manager.Meshes[name] = mesh;
}

bool ResourceManager::LoadShader(const std::string & name, const std::string & vs_path, const std::string & fs_path, const std::string & gs_path)
{
	auto& manager = GetInstance();
	string vs_code;
	string fs_code;
	string gs_code;
	try
	{
		ifstream vs_file(vs_path);
		ifstream fs_file(fs_path);

		stringstream vs_stream, fs_stream;
		vs_stream << vs_file.rdbuf();
		fs_stream << fs_file.rdbuf();

		vs_file.close();
		fs_file.close();

		vs_code = vs_stream.str();
		fs_code = fs_stream.str();

		if (!gs_path.empty())
		{
			ifstream gs_file(gs_path);
			stringstream gs_stream;
			gs_stream << gs_file.rdbuf();
			gs_file.close();
			gs_code = gs_stream.str();
		}
	}
	catch (const std::exception e)
	{
		cout << "ERROR::SHADER: Failed to read shader files" << endl;
		return false;
	}
	Shader* shader = new Shader();
	shader->compile(vs_code.c_str(), fs_code.c_str(), gs_path.empty() ? nullptr : gs_code.c_str());
	manager.Shaders[name] = shader;
	return true;
}

Texture2D * ResourceManager::GetTexture2D(const std::string & name)
{
	// TODO: if Texture2Ds[name] dosent exist
	auto& manager = GetInstance();
	return manager.Texture2Ds[name];
}

bool ResourceManager::LoadTexture2D(const std::string & name, const std::string & texture_path, const bool image_vertical_flip)
{
	auto& manager = GetInstance();
	stbi_set_flip_vertically_on_load(image_vertical_flip);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		// raise exception
	}
	else
	{
		GLuint internal_format;
		GLuint format;
		switch (nrChannels)
		{
		case 1:
			internal_format = GL_R8;
			format = GL_RED;
			break;
		case 3:
			internal_format = GL_RGB8;
			format = GL_RGB;
			break;
		case 4:
			internal_format = GL_RGBA8;
			format = GL_RGBA;
			break;
		default:
			internal_format = GL_RGBA8;
			format = GL_RGBA;
			break;
		}
		Texture2D* texture = new Texture2D();
		texture->setFormat(internal_format, format);
		texture->init(width, height, data);
		manager.Texture2Ds[name] = texture;
	}
	stbi_image_free(data);
	return data != nullptr;
}


