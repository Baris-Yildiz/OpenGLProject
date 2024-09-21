#include "TestTexture.h"

test::TestTexture::TestTexture() : m_Color{}
{
    float positions[] = {
         0.0f,  0.0f, 0.0f, 0.0f,   //0,1
         320.0f, 0.0f, 1.0f, 0.0f,  //0,0
         320.0f, 240.0f,1.0f, 1.0f, //1,0
         0.0f,  240.0f, 0.0f, 1.0f  //1,1
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    m_VertexArray = new VertexArray();
    m_VertexBuffer = new VertexBuffer(positions, sizeof(positions));
    m_VertexBufferLayout = new VertexBufferLayout();

    m_VertexBufferLayout->Push<float>(2);
    m_VertexBufferLayout->Push<float>(2);
    m_IndexBuffer = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));

    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_IndexBuffer, *m_VertexBufferLayout);

    m_Shader = new Shader("res/shaders/TextureLoad.shader");
    m_Shader->Bind();

    m_Texture = new Texture("res/textures/sample2.jpg");
    // bind texture to slot 0.
    unsigned int bindSlot = 0;
    m_Texture->Bind(bindSlot);
    
    m_Shader->SetUniform1i("u_Texture", bindSlot);
    
    m_Renderer = new Renderer();

    m_Translation = glm::vec3(m_Width / 2.0f - 160.0f, m_Height / 2.0f - 120.0f, 0.0f);
}

test::TestTexture::~TestTexture()
{
    delete m_Texture;
}

void test::TestTexture::OnUpdate(float dt)
{
}

void test::TestTexture::OnRender()
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

void test::TestTexture::OnImGuiRender()
{
}
