#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"

namespace test {

	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_Color[4];
		Texture* m_Texture;
	};
}