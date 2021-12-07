#include "Objective.h"

namespace Engine
{
	Objective::Objective(const std::string& objective) :
		m_name(objective)
	{

	}

	Objective::Objective(const std::string& objective, ObjectiveState state) :
		m_name(objective),
		m_state(state)
	{

	}

	ObjectiveState Objective::getState()
	{
		return m_state; 
	}

	std::string Objective::getName()
	{ 
		return m_name; 
	}

	void Objective::setState(ObjectiveState state)
	{ 
		m_state = state; 
		printf("Setting state of objective: %s to %d\n", m_name.c_str(), state);
	}

}