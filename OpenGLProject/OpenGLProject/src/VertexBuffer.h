#pragma once
#include "GL/glew.h"

class VertexBuffer {
private:
	unsigned int m_RendererID; //m is for "member"
public:
	VertexBuffer(const void* data, unsigned int size, GLenum mode = GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

