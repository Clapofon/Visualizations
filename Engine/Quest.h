#pragma once

#include <vector>
#include <string>

#include "Objective.h"

enum class QuestState
{
	COMPLETED,
	FAILED,
	PENDING,
	CURRENT
};

namespace Engine
{
	class Quest
	{
	public:
		Quest(const std::string& title, const std::string& desc);
		~Quest();

		void addObjective(const std::string& objective);

		void setState(QuestState state);
		void setObjectiveState(const std::string& objective, ObjectiveState state);
		void setLastObjectiveState(ObjectiveState state);
		void setCurrentObjectiveAsCompleted();

		QuestState getState() { return m_state; }
		std::string	getName() { return m_title; }
		std::string	getDescription() { return m_description; }
		std::vector<Objective> getObjectives() { return m_objectives; }
		Objective getCurrentObjective();

	private:
		std::string	m_title;
		std::string	m_description;
		std::vector<Objective> m_objectives;

		QuestState m_state = QuestState::PENDING;
	};
}
