#include "Texture2D.h"

Renderer::Texture2D::Texture2D(
	const GLuint width,
	const GLuint height,
	const unsigned char* data,
	const unsigned int chanels,
	const GLenum filter = GL_LINEAR,
	const GLenum wrapMode = GL_CLAMP_TO_EDGE)
	: m_width(width),
	m_height(height)
{
	switch (chanels)
	{
	case 4:
		m_mode = GL_RGBA;
		break;
	case 3:
		m_mode = GL_RGB;
		break;
	default:
		m_mode = GL_RGBA;
		break;
	}
	glGenTextures(1,&m_ID);
	glBindTexture(GL_TEXTURE_2D,m_ID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer::Texture2D::~Texture2D(){
	glDeleteTextures(1, &m_ID);
}

Renderer::Texture2D::Texture2D(Texture2D&& texture2D){
	m_ID = texture2D.m_ID;
	texture2D.m_ID = 0;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
}

void Renderer::Texture2D::bind() const{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

Renderer::Texture2D& Renderer::Texture2D::operator=(Texture2D&& texture2D) {
	glDeleteTextures(1, &m_ID);
	m_ID = texture2D.m_ID;
	texture2D.m_ID = 0;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
	return *this;
};
