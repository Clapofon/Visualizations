#pragma once

#include <string>

namespace Engine
{
	class Fact
	{
	public:
		Fact();
		~Fact();

		void setFactState(bool state);

		std::string getName() { return m_name; }
		bool getState() { return m_state; }

	private:

		std::string m_name;
		bool m_state = false;

	};

}