#pragma once
#include "GL/glew.h"
#include "string"

class Texture
{
private:
	unsigned int m_RendererID;
	const std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; //bpp = bits per pixel
public:
	Texture(const std::string& filepath);
	~Texture();


	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeigth() const { return m_Height; }
};

