#include "TestMenu.h"

test::TestMenu::TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer)
{
	
}

void test::TestMenu::OnImGuiRender()
{
	for (auto& it : m_Tests) {
		if (ImGui::Button(it.first.c_str())) { //for each test, create a button.
			m_CurrentTest = it.second();
		}
	}
}
