#pragma once

#include <string>

enum class ObjectiveState
{
	COMPLETED,
	FAILED,
	PENDING,
	CURRENT
};

namespace Engine
{

	class Objective
	{
	public:
		Objective(const std::string& objective);
		Objective(const std::string& objective, ObjectiveState state);

		ObjectiveState getState();
		std::string getName();

		void setState(ObjectiveState state);

	private:
		std::string m_name;

		ObjectiveState m_state = ObjectiveState::PENDING;
	};

}