#include "ShaderProgram.h"
#include <iostream>

namespace Renderer {
	Renderer::ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)){
			std::cerr << "VERTEX SHADER has errors!" << std::endl;
			return;
		}
		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			std::cerr << "FRAGMENT SHADER has errors!" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint succes;
		glGetProgramiv(m_ID, GL_LINK_STATUS,&succes);
		if (!succes) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR SHADER LINK: " << infoLog << std::endl;
		}
		else {
			m_isCompiled = true;
		}
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	ShaderProgram::~ShaderProgram(){
		glDeleteProgram(m_ID);
	}
	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = GL_FALSE;
	}
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = GL_FALSE;

		return *this;
	}
	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint succes;

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);

		if (!succes) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR SHADER COMPILE: " << infoLog << std::endl;
			return false;
		}
		return true;
	}

    void ShaderProgram::setInt(const std::string &name, GLint value) {
        glUniform1i(glGetUniformLocation(m_ID,name.c_str()),value);
    }
}