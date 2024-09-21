#pragma once
#include "Test.h"
#include "vector"
#include <functional>

namespace test {

	class TestMenu : public Test
	{
	private:
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
		Test*& m_CurrentTest;
	public:
		TestMenu(Test*& currentTestPointer);


		template<typename T>
		void RegisterTest(const std::string& name) {
			m_Tests.push_back(std::make_pair(name, []() {return new T();})); //[] () { return...} is a lambda function
		}

		void OnImGuiRender() override;
	};

}

