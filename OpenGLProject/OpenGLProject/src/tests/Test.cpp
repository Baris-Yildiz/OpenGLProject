#include "Test.h"

test::Test::Test()
{
	m_Width = 640;
	m_Height = 480;
	m_Translation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::ortho(0.0f, m_Width, 0.0f, m_Height, 0.0f, 1.0f);
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
}

test::Test::~Test()
{
	delete m_Renderer;
	delete m_Shader;
	delete m_VertexArray;
	delete m_IndexBuffer;
	delete m_VertexBuffer;
	delete m_VertexBufferLayout;
}
