#include "VertexArray.h"
#include "IndexBuffer.h"

VertexArray::VertexArray()
{
	//create vertex array. vertex arrays hold vertex buffers and index buffers.
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();	// bind vertex buffer to vertex array
	ib.Bind();	// bind index buffer to vertex array

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);	
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	
	
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
