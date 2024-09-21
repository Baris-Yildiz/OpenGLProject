#include "TestColorBatchRendering.h"

test::TestColorBatchRendering::TestColorBatchRendering()
    : m_Color1{ 84.0f, 192.0f, 138.0f, 255.0f },
    m_Color2{ 93.0f, 84.0f, 192.0f, 255.0f }
{
    for (int i = 0; i < 4; i++) {
        m_Color1[i] = m_Color1[i] / 255.0f;
        m_Color2[i] = m_Color2[i] / 255.0f;
    }
    float positions[] = {
         0.0f,  0.0f,  m_Color1[0], m_Color1[1], m_Color1[2], m_Color1[3],
         30.0f, 0.0f,  m_Color1[0], m_Color1[1], m_Color1[2], m_Color1[3],
         30.0f, 30.0f, m_Color1[0], m_Color1[1], m_Color1[2], m_Color1[3],
         0.0f,  30.0f, m_Color1[0], m_Color1[1], m_Color1[2], m_Color1[3],

         40.0f,  0.0f,  m_Color2[0], m_Color2[1], m_Color2[2], m_Color2[3],
         70.0f, 0.0f,   m_Color2[0], m_Color2[1], m_Color2[2], m_Color2[3],
         70.0f, 30.0f,  m_Color2[0], m_Color2[1], m_Color2[2], m_Color2[3],
         40.0f,  30.0f, m_Color2[0], m_Color2[1], m_Color2[2], m_Color2[3]
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,

        4, 5, 6,
        4, 6, 7
    };

    m_VertexArray = new VertexArray();
    m_VertexBuffer = new VertexBuffer(positions, sizeof(positions));
    m_VertexBufferLayout = new VertexBufferLayout();

    m_VertexBufferLayout->Push<float>(2);
    m_VertexBufferLayout->Push<float>(4, GL_TRUE);
    m_IndexBuffer = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));

    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_IndexBuffer, *m_VertexBufferLayout);
    m_Shader = new Shader("res/shaders/ColorBatchRendering.shader");

    m_Shader->Bind();
    m_Renderer = new Renderer();

    m_Translation = glm::vec3(m_Width / 2.0f - 35.0f, m_Height / 2.0f - 15.0f , 0.0f);
}

test::TestColorBatchRendering::~TestColorBatchRendering()
{

}

void test::TestColorBatchRendering::OnUpdate(float dt)
{
}

void test::TestColorBatchRendering::OnRender()
{
    m_Renderer->Clear();

    m_Shader->Bind();

    m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
    m_Shader->SetUniformMat4f("u_MVP", mvp);

    m_VertexArray->Bind();
    m_IndexBuffer->Bind();

    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void test::TestColorBatchRendering::OnImGuiRender()
{
}
