#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size, GLenum mode)
{
    // vertex buffers are buffers/memory arrays that hold "vertices".

    // create a buffer and assign its ID to m_RendererID.
    glGenBuffers(1, &m_RendererID); 

    // bind current "array_buffer" to buffer
    Bind();

    // feed current bound "array buffer" the provided data. 
    // GL_STATIC_DRAW is used for vertices that are not going to be changed throughout the program
    glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
