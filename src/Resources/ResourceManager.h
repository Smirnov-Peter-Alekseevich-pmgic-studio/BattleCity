#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class ShaderProgram;
}



class ResourceManager {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> LoadShaders(const std::string& shaderName, const std::string& vertexPath,const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shaderName);
private:
	const std::string getFileString(const std::string& path);
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> shaderProgramsMap;
	shaderProgramsMap m_shaderPrograms;
	std::string m_path;
};