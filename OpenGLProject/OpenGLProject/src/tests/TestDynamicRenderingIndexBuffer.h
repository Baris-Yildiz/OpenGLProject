#pragma once
#include "Test.h"
#include "Renderer.h"
#include "VertexType.h"
#include "Utilities.h"

namespace test {

	class TestDynamicRenderingIndexBuffer : public Test
	{
	public:
		TestDynamicRenderingIndexBuffer();
		~TestDynamicRenderingIndexBuffer();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
	};
}
