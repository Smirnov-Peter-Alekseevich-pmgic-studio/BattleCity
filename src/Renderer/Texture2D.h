#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/vec2.hpp>
#include <map>

namespace Renderer {
	class Texture2D {
	public:
	    struct SubTexture2D{
	        glm::vec2 leftBottomUV;
	        glm::vec2 rightTopUV;

	        SubTexture2D(
	                const glm::vec2& _leftBottomUV,
	                const glm::vec2& _rightTopVM)
	                : leftBottomUV(_leftBottomUV),
	                rightTopUV(_rightTopVM){}
	        SubTexture2D()
	        :leftBottomUV(0.f),
	        rightTopUV(1.f){}
	    };
		Texture2D(
			const GLuint width,const GLuint height,
			const unsigned char* data,
			const unsigned int chanels,
			const GLenum filter,
			const GLenum wrapMode
		);
		Texture2D() = delete;
		~Texture2D();
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2D);
		Texture2D(Texture2D&& texture2D);
        const SubTexture2D& getSubTexture(const std::string& name) const;
		void bind() const;
        void addSubTexture(const std::string& nameSubTexture,const glm::vec2& leftBottomVM,const glm::vec2& rightTopVM);
        unsigned int width() const {return m_width;};
        unsigned int height() const {return m_height;};
	private:
		GLuint m_ID;
		GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;
		std::map<std::string,SubTexture2D> m_subTextures;
    };
}