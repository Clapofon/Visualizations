#include "QuestSystem.h"

namespace Engine
{

	QuestSystem::QuestSystem()
	{

	}

	QuestSystem::~QuestSystem()
	{

	}


	void QuestSystem::addQuest(Quest quest)
	{
		quest.setState(QuestState::CURRENT);
		m_questList.push_back(quest);
	}

	void QuestSystem::addFact(Fact fact)
	{
		std::string name = fact.getName();
		auto it = m_factMap.find(name);

		if (it == m_factMap.end())
		{
			m_factMap.insert(make_pair(name, fact));
		}
		else
		{
			printf("QuestSystem error: addFact failed, fact already exists: %s\n", name.c_str());
		}
	}

	void QuestSystem::setCurrentQuest(const std::string& quest)
	{
		for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getName() == quest)
			{
				m_currentQuest = quest;
				m_questList[i].setState(QuestState::CURRENT);
			}
		}
	}

	void QuestSystem::setFactState(const std::string& fact, bool state)
	{
		auto it = m_factMap.find(fact);

		if (it != m_factMap.end())
		{
			it->second.setFactState(state);
		}
		else
		{
			printf("QuestSystem error: setFactState failed, no such fact as %s\n", fact.c_str());
		}
	}

	void QuestSystem::markQuestAsCompleted(const std::string& quest)
	{
		for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getName() == quest)
			{
				m_questList[i].setState(QuestState::COMPLETED);
			}
		}
	}

	void QuestSystem::markQuestAsFailed(const std::string& quest)
	{
		for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getName() == quest)
			{
				m_questList[i].setState(QuestState::FAILED);
			}
		}
	}

	Quest QuestSystem::getCurrentQuest()
	{
		for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getState() == QuestState::CURRENT)
			{
				return m_questList[i];
			}
		}
		Quest empty("empty", "empty");
		return empty;
	}

	bool QuestSystem::getFactState(const std::string& fact)
	{
		auto it = m_factMap.find(fact);

		if (it != m_factMap.end())
		{
			return it->second.getState();
		}
		else
		{
			printf("QuestSystem error: getFactState failed, no such fact as %s\n", fact.c_str());
			return false;
		}
	}

	std::vector<Quest> QuestSystem::getAllQuests()
	{
		return m_questList;
	}

	void QuestSystem::next()
	{
		std::string name = getCurrentQuest().getName();
		
		/*for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getName() == name)
			{
				if (i == m_questList.size() - 1)
				{
					m_questList[m_questList.size() - 1].setState(QuestState::PENDING);
					m_questList[0].setState(QuestState::CURRENT);
				}
				else
				{
					m_questList[i + 1].setState(QuestState::CURRENT);
				}
			}
		}*/

		for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getName() == name)
			{
				m_questList[i].setState(QuestState::PENDING);
				if (i + 1 < m_questList.size())
				{
					m_questList[i + 1].setState(QuestState::CURRENT);
				}
				else 
				{
					m_questList[0].setState(QuestState::CURRENT);
				}
			}
		}

	}

	void QuestSystem::previous()
	{
		std::string name = getCurrentQuest().getName();
		
		/*for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getName() == name)
			{
				if (i == 0)
				{
					m_questList[0].setState(QuestState::PENDING);
					m_questList[m_questList.size() - 1].setState(QuestState::CURRENT);
				}
				else
				{
					m_questList[i - 1].setState(QuestState::CURRENT);
				}
			}
		}*/

		for (int i = 0; i < m_questList.size(); i++)
		{
			if (m_questList[i].getName() == name)
			{
				m_questList[i].setState(QuestState::PENDING);
				if (i > 0)
				{
					m_questList[i - 1].setState(QuestState::CURRENT);
				}
				else
				{
					m_questList[m_questList.size() - 1].setState(QuestState::CURRENT);
				}
			}
		}
	}
}