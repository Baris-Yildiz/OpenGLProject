#include "TestClearColor.h"

test::TestClearColor::TestClearColor() : m_Color {0, 0, 0, 0}
{
}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::OnUpdate(float dt)
{

}

void test::TestClearColor::OnRender()
{
	glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void test::TestClearColor::OnImGuiRender()
{
	ImGui::ColorPicker4("Background Color", m_Color);
}
