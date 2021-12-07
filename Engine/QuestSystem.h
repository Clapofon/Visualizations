#pragma once

#include <string>
#include <map>

#include "Quest.h"
#include "Fact.h"

namespace Engine
{
	class QuestSystem
	{
	public:
		QuestSystem();
		~QuestSystem();


		void addQuest(Quest quest);
		void addFact(Fact fact);

		void setCurrentQuest(const std::string& quest);
		void setFactState(const std::string& fact, bool state);

		void markQuestAsCompleted(const std::string& quest);
		void markQuestAsFailed(const std::string& quest);

		Quest getCurrentQuest();
		bool getFactState(const std::string& fact);

		std::vector<Quest> getAllQuests();

		void next();
		void previous();

	private:

		std::string m_currentQuest;

		std::vector<Quest> m_questList;
		std::map<std::string, Fact> m_factMap;
	};

}
