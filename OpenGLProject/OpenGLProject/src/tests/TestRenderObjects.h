#pragma once
#include "Test.h"
#include "Renderer.h"

namespace test {

	class TestRenderObjects : public Test
	{
	public:
		TestRenderObjects();
		~TestRenderObjects();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_Color[4];
	};
}

