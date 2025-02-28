#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0), m_BPP(0), m_Width(0), m_Height(0), m_LocalBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);	//flip texture vertically, this is an opengl thing.

	//load image and write the width, height, bpp attributes of it. 
	//last parameter is the desired channels, for our case it is 4 (RGBA)
	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	//set currently bound texture parameters. (Texture properties)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//other parameters of the texture. 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	UnBind();

	//free buffer if there is data in it.
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	//opengl stores textures in 32 slots. we can specify which slot we want to bind.
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
