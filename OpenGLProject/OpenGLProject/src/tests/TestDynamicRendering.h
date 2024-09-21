#pragma once
#include "Test.h"
#include "Renderer.h"
#include "VertexType.h"
#include "Utilities.h"

namespace test {

	class TestDynamicRendering : public Test
	{
	public:
		TestDynamicRendering();
		~TestDynamicRendering();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float x1, y1, x2, y2 = 0.0f;
		float width1, width2, height1, height2 = 0.0f;


	};
}
