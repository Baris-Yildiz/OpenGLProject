#include "TestColorAnimation.h"

test::TestColorAnimation::TestColorAnimation() : m_Color{ 0.8f, 0.3f, 0.8f, 1.0f }
{
    float positions[] = {
         m_Width / 2.0f, 3.0f * m_Height / 4.0f,
         m_Width / 4.0f, m_Height / 2.0f,
         m_Width / 2.0f, m_Height / 4.0f,
         3.0f * m_Width / 4.0f, m_Height / 2.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };


    m_VertexArray = new VertexArray();
    m_VertexBuffer = new VertexBuffer(positions, sizeof(positions));
    m_VertexBufferLayout = new VertexBufferLayout();

    m_VertexBufferLayout->Push<float>(2);
    m_IndexBuffer = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));

    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_IndexBuffer, *m_VertexBufferLayout);
    m_Shader = new Shader("res/shaders/Basic.shader");

    m_Shader->Bind();
    m_Renderer = new Renderer();

    fadeColorAnimation = new Animation();
    fadeColorAnimation->SetStartTime();
}

test::TestColorAnimation::~TestColorAnimation()
{
	
}

void test::TestColorAnimation::OnUpdate(float dt)
{
}

void test::TestColorAnimation::OnRender()
{
    m_Renderer->Clear();
    float rValue = fadeColorAnimation->GetPowerParameter(0.25f, 2, 1);

    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", rValue, m_Color[1], m_Color[2], m_Color[3]);

    glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
    m_Shader->SetUniformMat4f("u_MVP", mvp);

    m_VertexArray->Bind();
    m_IndexBuffer->Bind();

    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void test::TestColorAnimation::OnImGuiRender()
{
}
