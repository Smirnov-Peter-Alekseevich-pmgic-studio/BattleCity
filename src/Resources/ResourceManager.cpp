#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executablePath){
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

ResourceManager::~ResourceManager(){
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders(const std::string& shaderName, const std::string& vertexPath,const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString == "") {
		std::cerr << "vertex shader is not found" << std::endl;
		return nullptr;
	}
	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString == "") {
		std::cerr << "fragment shader is not found" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>&newShader = m_shaderPrograms.emplace(shaderName,std::make_shared<Renderer::ShaderProgram>(vertexString,fragmentString)).first->second;
	if (newShader->isCompiled()) {
		return newShader;
	}
	std::cerr << "Can't load shader program: " << std::endl << "Vertex: " << vertexPath << std::endl << "Fragment: " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(const std::string& shaderName){
	shaderProgramsMap::const_iterator iterator = m_shaderPrograms.find(shaderName);
	if (iterator != m_shaderPrograms.end()) {
		return iterator->second;
	}
	std::cerr << "Can't find shader program: " << shaderName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTexture(const std::string& textureName, const std::string& path){
	int chanels = 0;
	int width = 0;
	int height = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path + "/" + path).c_str(),&width,&height,&chanels,0);
	if (!pixels) {
		std::cerr << "Can't load image: " << textureName << std::endl;
		return nullptr;
	}
	std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName, std::make_shared<Renderer::Texture2D>(width, height, pixels, chanels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::GetTexture(const std::string& textureName){
	texturesMap::const_iterator iterator = m_textures.find(textureName);
	if (iterator != m_textures.end()) {
		return iterator->second;
	}
	std::cerr << "Can't find texture: " << textureName << std::endl;
	return nullptr;
}

const std::string ResourceManager::getFileString(const std::string& path){
	std::ifstream file(m_path + "/" + path.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "File is not open:(" << std::endl;
		std::cerr << "name: " << path << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
