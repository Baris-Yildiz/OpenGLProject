#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Animation.h"

namespace test {

	class TestColorAnimation : public Test
	{
	public:
		TestColorAnimation();
		~TestColorAnimation();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_Color[4];
		Animation* fadeColorAnimation;
	};
}