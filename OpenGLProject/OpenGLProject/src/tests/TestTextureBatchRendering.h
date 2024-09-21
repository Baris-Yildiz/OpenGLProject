#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"

namespace test {
	//render two textures with batch rendering.
	class TestTextureBatchRendering : public Test
	{
	public:
		TestTextureBatchRendering();
		~TestTextureBatchRendering();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Texture* m_Texture1;
		Texture* m_Texture2;
	};
}