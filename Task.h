#ifndef TASK_H
#define TASK_H

#include "Project.h"
#include "Client.h"
#include "Date.h"


#include <string>
#include <utility>
#include <vector>

using namespace std;

class Collaborator;

class Task
{
private:
	int ID;
	static int lastID;
	string name;
	string description;
	unsigned int effort;
	vector< pair<Collaborator*, unsigned int> > collaborators;
	vector<Task*> dependencies;
	vector<Task*> dependants;
public:
	Task(string name, unsigned int effort){this->name = name; this->effort = effort;};
	//Task(){};
	void setName(string nm){ name = nm; };
	void setEffort(unsigned int ef){ effort = ef; };
	bool operator==(Task& t2);
	class TaskComparator
	{
	public:
		virtual bool operator()(const Task& t1, const Task& t2)=0;
	};
	class TaskComparatorAlphabetic : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.name < t2.name; };
	};
	class TaskComparatorPriority : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.getPriority() < t2.getPriority(); };
	};
	
	
	string getName() const { return this->name; };
	int getID() const { return this->ID; };
	int getPriority() const 
	{ 
		double sum = calculateEstimatedTime();
		for (size_t i = 0; i < dependants.size(); i++)
			sum += double(dependants.at(i)->getPriority()) / dependencies.size();
		return sum;
	};

	int calculateEstimatedTime() const
	{ 
		int sum = 0; 
		for (size_t i = 0; i < collaborators.size(); i++) 
			sum += collaborators.at(i).second; 
		if (sum == 0) 
			return INT_MAX; 
		else return int(double (effort) / sum + .5);
	};
	int calculateTimeToCompletion() const 
	{ 
		int sum = this->calculateEstimatedTime(); 
		for (size_t i = 0; i < dependencies.size(); i++) 
			sum += dependencies.at(i)->calculateTimeToCompletion();
		return sum; 
	};
	bool isReady()
	{ 
		for (size_t i = 0; i < dependencies.size(); ++i)
		if (dependencies.at(i)->effort != 0)
			return false;
		return true;
	}
	double tick()
	{
		if (!isReady())
			return -1;
		double sum = 0;
		for (size_t i = 0; i < collaborators.size(); ++i)
		{
			sum += collaborators.at(i).second * collaborators.at(i).first->getCost();
			if(effort > 0) effort -= collaborators.at(i).second;
			if (effort <= 0)
			{
				effort = 0;
				collaborators.at(i).first->removeTask(this);
			}
		}
		return sum;
	}
};
#endif