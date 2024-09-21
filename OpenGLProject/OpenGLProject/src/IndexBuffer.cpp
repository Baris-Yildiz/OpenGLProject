#include "IndexBuffer.h"
#include "GL/glew.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
    m_Count = count;
    // index buffers (element array buffers) are buffers that hold indexes. 
    // These indexes refer to the indexes of vertices in the vertex buffer.
    // Makes it easier to draw shapes with multiple points.

    glGenBuffers(1, &m_RendererID);

    Bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); 
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
