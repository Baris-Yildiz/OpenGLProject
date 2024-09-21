#include "TestTextureBatchRendering.h"

test::TestTextureBatchRendering::TestTextureBatchRendering()
{
    float positions[] = {
         0.0f,  0.0f,   0.0f, 0.0f, 0.0f,
         90.0f, 0.0f,   1.0f, 0.0f, 0.0f,
         90.0f, 90.0f,  1.0f, 1.0f, 0.0f,
         0.0f,  90.0f,  0.0f, 1.0f , 0.0f,

         210.0f,  0.0f,   0.0f, 0.0f, 1.0f,
         300.0f, 0.0f,    1.0f, 0.0f, 1.0f,
         300.0f, 90.0f,  1.0f, 1.0f, 1.0f,
         210.0f,  90.0f,  0.0f, 1.0f,  1.0f
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

    m_VertexBufferLayout->Push<float>(2); //push positions.
    m_VertexBufferLayout->Push<float>(2); //push texture coordinates.
    m_VertexBufferLayout->Push<float>(1); //push texture index float.

    m_IndexBuffer = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));

    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_IndexBuffer, *m_VertexBufferLayout);

    m_Shader = new Shader("res/shaders/TextureBatchRendering.shader");
    m_Shader->Bind();


    //load 2 textures
    m_Texture1 = new Texture("res/textures/sample.jpg");
    m_Texture2 = new Texture("res/textures/sample2.jpg");
    // set bind positions
    m_Texture1->Bind(0);
    m_Texture2->Bind(1);

    int samplers[2] = { 0 , 1 };
    m_Shader->SetUniform1iv("u_Textures", 2, samplers);
    
    m_Renderer = new Renderer();

    m_Translation = glm::vec3(m_Width / 2.0f - 150.0f, m_Height / 2.0f - 45.0f, 0.0f);
}

test::TestTextureBatchRendering::~TestTextureBatchRendering()
{
    delete m_Texture1;
    delete m_Texture2;
}

void test::TestTextureBatchRendering::OnUpdate(float dt)
{
}

void test::TestTextureBatchRendering::OnRender()
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

void test::TestTextureBatchRendering::OnImGuiRender()
{
}
