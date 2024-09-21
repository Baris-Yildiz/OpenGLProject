#include "TestRenderObjects.h"

test::TestRenderObjects::TestRenderObjects() : m_Color{0,0,0,0}
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

    m_Translation = glm::vec3(0.0f, 0.0f, 0.0f);
    // projection matrix is used to translate our vertex positions into the screen space.
    // normally, opengl assumes that the screen space is a 1x1 square, with this projection matrix, we can redefine it in a way.
    // this projection matrix technically states that the left extreme of our screen is 0, the right extreme is "m_Width" and the same 
    // logic for y and z axis.
    m_ProjectionMatrix = glm::ortho(0.0f, m_Width, 0.0f, m_Height, 0.0f, 1.0f);
    
    //view matrix is our camera position. we made it so that every object drawn gets translated -100 units (100 units to the left)
    // this is essentially like a camera that moved 100 units to the right.
    m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));

    // this is a matrix that represents a certain model's (object's) transform. the view matrix should be applied to every object
    // while this matrix is only applied to a certain object.
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 100, 0));


}

test::TestRenderObjects::~TestRenderObjects()
{
    
}

void test::TestRenderObjects::OnUpdate(float dt)
{

}

void test::TestRenderObjects::OnRender()
{
    m_Renderer->Clear();

    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
    m_Shader->SetUniformMat4f("u_MVP", mvp);

    m_VertexArray->Bind();
    m_IndexBuffer->Bind();

    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

    m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 0)); //another object can be drawn only by resetting the model matrix.
    mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void test::TestRenderObjects::OnImGuiRender()
{
    ImGui::SliderFloat3("Translation", &(m_Translation.x), 0, m_Width);
    ImGui::ColorPicker4("button", &m_Color[0]);
    
}
