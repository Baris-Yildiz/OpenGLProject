#pragma once
#include "Test.h"
#include "Renderer.h"

namespace test {
	//batch rendering: rendering multiple properties with only 1 draw call, instead of multiple calls. e.g. rendering
	// two different objects with different colors in a single draw call.
	class TestColorBatchRendering : public Test
	{
	public:
		TestColorBatchRendering();
		~TestColorBatchRendering();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_Color1[4];
		float m_Color2[4];
	};
}
