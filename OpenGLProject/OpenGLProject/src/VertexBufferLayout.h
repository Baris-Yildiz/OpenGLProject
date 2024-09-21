#pragma once
#include "vector"
#include "GL/glew.h"
#include "VertexType.h"

struct VertexBufferElement //parameters of glVertexAttribPointer()
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{			
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			case VERTEX3POS4COL: return sizeof(Vertex3Pos4Col);
		default:
			break;
		}
		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {}

	template<typename T> // make a generic template of Push function. the body is called when the given T type is not supported.
	void Push(unsigned int count, unsigned char normalized = GL_FALSE) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count, unsigned char normalized) {
		VertexBufferElement vertexBufferElement = { GL_FLOAT, count, normalized };
		m_Elements.push_back(vertexBufferElement);
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count, unsigned char normalized) {
		VertexBufferElement vertexBufferElement = { GL_UNSIGNED_INT, count, normalized };
		m_Elements.push_back(vertexBufferElement);
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count, unsigned char normalized) {
		VertexBufferElement vertexBufferElement = { GL_UNSIGNED_BYTE, count, normalized };
		m_Elements.push_back(vertexBufferElement);
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	template<>
	void Push<Vertex3Pos4Col>(unsigned int count, unsigned char normalized) {
		VertexBufferElement vertexBufferElement = { VERTEX3POS4COL, count, normalized };
		m_Elements.push_back(vertexBufferElement);
		m_Stride += count * VertexBufferElement::GetSizeOfType(VERTEX3POS4COL);
	}

	inline unsigned int getStride() const { return m_Stride; }
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
};

