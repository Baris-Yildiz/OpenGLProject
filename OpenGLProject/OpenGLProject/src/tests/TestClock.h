#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Utilities.h"
#include "sstream"

namespace test {
	//batch rendering: rendering multiple properties with only 1 draw call, instead of multiple calls. e.g. rendering
	// two different objects with different colors in a single draw call.
	class TestClock : public Test
	{
	public:
		TestClock();
		~TestClock();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Vertex3Pos4Col* CreateSevenDigitDisplay(int target, Vertex3Pos4Col* arr, float x, float y, float width, float height);
		Vertex3Pos4Col* CreateSemiColon(Vertex3Pos4Col* arr, float x, float y, float size, float offset);

		float m_displayWidth, m_displayHeight;
		std::string* m_DigitMap; 
	};
}