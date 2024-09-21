#include "TestDynamicRendering.h"

test::TestDynamicRendering::TestDynamicRendering() : x1(0), x2(0), y1(0), y2(0), height1(0), height2(0), width1(0), width2(0)
{
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,

        4, 5, 6,
        4, 6, 7
    };

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

test::TestDynamicRendering::~TestDynamicRendering()
{
}

void test::TestDynamicRendering::OnUpdate(float dt)
{
}

void test::TestDynamicRendering::OnRender()
{
    m_Renderer->Clear();

    m_Shader->Bind();

    m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
    m_Shader->SetUniformMat4f("u_MVP", mvp);

    m_VertexArray->Bind();

    Vertex3Pos4Col vertices[8];

    std::array<Vertex3Pos4Col, 4> arr = Utilities::CreateQuadPositions(x1, y1, width1, height1);
    std::array<Vertex3Pos4Col, 4> arr2 = Utilities::CreateQuadPositions(x2, y2, width2, height2);

    for (int i = 0; i < 4; i++) {
        arr[i].Color = { 1, 1, 1, 1 };
        arr2[i].Color = { 1, 1, 1, 1 };
    }

    memcpy(vertices, arr.data(), arr.size() * sizeof(Vertex3Pos4Col));
    memcpy(vertices + arr.size(), arr2.data(), arr2.size() * sizeof(Vertex3Pos4Col));

    m_VertexBuffer->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    m_IndexBuffer->Bind();

    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void test::TestDynamicRendering::OnImGuiRender()
{
    ImGui::SliderFloat("xPosition 1", &x1, 0, m_Width);
    ImGui::SliderFloat("yPosition 1", &y1, 0, m_Height);

    ImGui::SliderFloat("xPosition 2", &x2, 0, m_Width);
    ImGui::SliderFloat("yPosition 2", &y2, 0, m_Height);

    ImGui::SliderFloat("Width 1", &width1, 0, 100.0f);
    ImGui::SliderFloat("Width 2", &width2, 0, 100.0f);

    ImGui::SliderFloat("Height 1", &height1, 0, 100.0f);
    ImGui::SliderFloat("Height 2", &height2, 0, 100.0f);
}
