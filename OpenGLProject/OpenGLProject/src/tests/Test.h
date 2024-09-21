#pragma once
#include "imgui/imgui.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include "Renderer.h"

namespace test {

	class Test
	{
	private:
		const std::string testName;
	protected:
		Renderer* m_Renderer = nullptr;
		Shader* m_Shader = nullptr;
		VertexArray* m_VertexArray = nullptr;
		IndexBuffer* m_IndexBuffer = nullptr;
		VertexBuffer* m_VertexBuffer = nullptr;
		VertexBufferLayout* m_VertexBufferLayout = nullptr;

		glm::mat4 m_ProjectionMatrix;
		glm::vec3 m_Translation;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ModelMatrix;

		float m_Width, m_Height;
	public:

		Test();
		~Test();

		virtual void OnUpdate(float dt) {};
		virtual void OnRender() {};	//things to do when we render the test
		virtual void OnImGuiRender() {};	//render imgui elements.
	};
}

