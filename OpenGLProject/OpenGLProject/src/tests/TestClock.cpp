#include "TestClock.h"
#include "string"

test::TestClock::TestClock() : m_displayHeight(5.0f), m_displayWidth(50.0f)
{
    m_DigitMap = new std::string[7];
    m_DigitMap[0] = "0011111011";
    m_DigitMap[1] = "1011011111";
    m_DigitMap[2] = "1011011011";
    m_DigitMap[3] = "1000111011";
    m_DigitMap[4] = "1111100111";
    m_DigitMap[5] = "1010001010";
    m_DigitMap[6] = "1101111111";

    uint32_t indices[46*6];
    uint32_t offset = 0;

    for (size_t i = 0; i < 46*6; i += 6) {
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
    m_VertexBuffer = new VertexBuffer(nullptr, sizeof(Vertex3Pos4Col) * 46 * 4, GL_DYNAMIC_DRAW);
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

test::TestClock::~TestClock()
{
    delete[] m_DigitMap;
}

void test::TestClock::OnUpdate(float dt)
{
}

void test::TestClock::OnRender()
{
    m_Renderer->Clear();

    m_Shader->Bind();

    m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
    m_Shader->SetUniformMat4f("u_MVP", mvp);

    m_VertexArray->Bind();

    std::array<Vertex3Pos4Col, 46 * 4> vertices;
    Vertex3Pos4Col* buffer = vertices.data();

    const char* currentTime = Utilities::GetFormattedCurrentTime("%H%M%S");

    buffer = CreateSevenDigitDisplay(currentTime[0] - '0', buffer, m_Width / 8.0f, m_Height / 2.0f, m_displayWidth, m_displayHeight);
    buffer = CreateSevenDigitDisplay(currentTime[1] - '0', buffer, 2* m_Width /8.0f, m_Height / 2.0f, m_displayWidth, m_displayHeight);

    buffer = CreateSemiColon(buffer, 2.75f * m_Width / 8.0f, m_Height / 2.0f, m_displayHeight, m_displayWidth / 2.0f);

    buffer = CreateSevenDigitDisplay(currentTime[2] - '0', buffer, 3.5 * m_Width / 8.0f, m_Height / 2.0f, m_displayWidth, m_displayHeight);
    buffer = CreateSevenDigitDisplay(currentTime[3] - '0', buffer, 4.5 * m_Width / 8.0f, m_Height / 2.0f, m_displayWidth, m_displayHeight);

    buffer = CreateSemiColon(buffer, 5.25f * m_Width / 8.0f, m_Height / 2.0f, m_displayHeight, m_displayWidth / 2.0f);

    buffer = CreateSevenDigitDisplay(currentTime[4] - '0', buffer, 6*m_Width / 8.0f, m_Height / 2.0f, m_displayWidth, m_displayHeight);
    buffer = CreateSevenDigitDisplay(currentTime[5] - '0', buffer, 7* m_Width / 8.0f, m_Height / 2.0f, m_displayWidth, m_displayHeight);

    m_VertexBuffer->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex3Pos4Col), vertices.data());
    m_IndexBuffer->Bind();

    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void test::TestClock::OnImGuiRender()
{
}

Vertex3Pos4Col* test::TestClock::CreateSevenDigitDisplay(int target, Vertex3Pos4Col* arr, float x, float y, float width, float height)
{
    for (int i = 0; i < 7; i++) {
        char canOpenLed = m_DigitMap[i][target];
        if (canOpenLed == '1') {
            if (i == 0) {
                arr = Utilities::CreateQuadPositionsAndFillArray(arr, x, y, width, height);
            }
            else if (i == 1) {
                arr = Utilities::CreateQuadPositionsAndFillArray(arr, x, y + width, width, height);
            }
            else if (i == 2) {
                arr = Utilities::CreateQuadPositionsAndFillArray(arr, x, y - width, width, height);
            }
            else if (i == 3) {
                arr = Utilities::CreateQuadPositionsAndFillArray(arr, x - (width / 2.0f) - height, y + width / 2.0f, height, width - 2 * height);
            }
            else if (i == 4) {
                arr = Utilities::CreateQuadPositionsAndFillArray(arr, x + (width / 2.0f) + height, y + width / 2.0f, height, width - 2 * height);
            }
            else if (i == 5) {
                arr = Utilities::CreateQuadPositionsAndFillArray(arr, x - (width / 2.0f) - height, y - width / 2.0f, height, width - 2 * height);
            }
            else if (i == 6) {
                arr = Utilities::CreateQuadPositionsAndFillArray(arr, x + (width / 2.0f) + height, y - width / 2.0f, height, width - 2 * height);
            }
        }
    }

    return arr;
}

Vertex3Pos4Col* test::TestClock::CreateSemiColon(Vertex3Pos4Col* arr, float x, float y, float size, float offset)
{
    arr = Utilities::CreateQuadPositionsAndFillArray(arr, x, y + offset, size, size);
    arr = Utilities::CreateQuadPositionsAndFillArray(arr, x, y - offset, size, size);
    return arr;
}
