#include "TestDynamicRenderingIndexBuffer.h"

test::TestDynamicRenderingIndexBuffer::TestDynamicRenderingIndexBuffer()
{
    const size_t maxQuadCount = 1000;
    const size_t maxVertexCount = 4000;
    const size_t maxIndexCount = 6000;

    uint32_t indices[maxIndexCount];
    uint32_t offset = 0;

    //create 6000 index draw calls.
    for (size_t i = 0; i < maxIndexCount; i += 6) {
        indices[i] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;


        indices[i + 3] = 0 + offset;
        indices[i + 4] = 2 + offset;
        indices[i + 5] = 3 + offset;

        offset += 4;
    }

    m_VertexArray = new VertexArray();

    // allocate empty memory capable of holding 1000 Vertexes (arbitrary but big number).
    m_VertexBuffer = new VertexBuffer(nullptr, sizeof(Vertex3Pos4Col) * 1000, GL_DYNAMIC_DRAW);
    //then, we will fill this array in the render loop.

    m_VertexBufferLayout = new VertexBufferLayout();

    m_VertexBufferLayout->Push<float>(3);
    m_VertexBufferLayout->Push<float>(4);
    m_IndexBuffer = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));

    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_IndexBuffer, *m_VertexBufferLayout);
    m_Shader = new Shader("res/shaders/ColorBatchRendering.shader");
    m_Shader->Bind();

    m_Renderer = new Renderer();
}

test::TestDynamicRenderingIndexBuffer::~TestDynamicRenderingIndexBuffer()
{
}

void test::TestDynamicRenderingIndexBuffer::OnUpdate(float dt)
{
}

void test::TestDynamicRenderingIndexBuffer::OnRender()
{
    m_Renderer->Clear();

    m_Shader->Bind();
    
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
    m_Shader->SetUniformMat4f("u_MVP", mvp);

    m_VertexArray->Bind();

    std::array<Vertex3Pos4Col, 1000> vertices;
    Vertex3Pos4Col* buffer = vertices.data();

    for (float x = 0; x < m_Width; x+=100) {
        for (float y = 0; y < m_Height; y+=100) {
            buffer = Utilities::CreateQuadPositionsAndFillArray(buffer, x, y, 50.0f, 50.0f);
        }
    }

    m_VertexBuffer->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex3Pos4Col), vertices.data());
    m_IndexBuffer->Bind();

    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void test::TestDynamicRenderingIndexBuffer::OnImGuiRender()
{
}
