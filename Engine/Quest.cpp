#include "Quest.h"

namespace Engine
{
	Quest::Quest(const std::string& title, const std::string& desc) :
		m_title(title),
		m_description(desc)
	{

	}

	Quest::~Quest()
	{

	}

	void Quest::addObjective(const std::string& objective)
	{
		m_objectives.push_back(Objective(objective));
	}

	void Quest::setState(QuestState state)
	{
		m_state = state;
	}

	void Quest::setObjectiveState(const std::string& objective, ObjectiveState state)
	{
		for (int i = 0; i < m_objectives.size(); i++)
		{
			if (m_objectives[i].getName() == objective)
			{
				m_objectives[i].setState(state);
				printf("Setting state of objective: %s to %d\n", objective.c_str(), state);
			}
		}
	}

	void Quest::setLastObjectiveState(ObjectiveState state)
	{
		m_objectives.back().setState(state);
	}

	void Quest::setCurrentObjectiveAsCompleted()
	{
		setObjectiveState(getCurrentObjective().getName(), ObjectiveState::COMPLETED);

	}

	Objective Quest::getCurrentObjective()
	{
		for (int i = 0; i < m_objectives.size(); i++)
		{
			if (m_objectives[i].getState() == ObjectiveState::CURRENT)
			{
				printf("Returning Current objective: %s\n", m_objectives[i].getName().c_str());
				return m_objectives[i];
			}
		}
	}
}