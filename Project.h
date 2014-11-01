#ifndef PROJECT_H
#define PROJECT_H


#include "Task.h"
#include "Collaborator.h"
#include "Client.h"
#include "Date.h"
#include "Application.h"

#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

/*
Project Class:
Cada projecto vai ser composto/identificado:
por nome,
por um tipo,
para facilitar a identifica��o do projecto ser� atribuido um ID a cada um,
tem um prazo associado,
� composto por tarefas,
colaboradores, pois cada projecto vai ser implementado por colaboradores diferentes.
tem um cliente associado.
*/

using namespace std;

class Client;
class Task;
class Collaborator;

class Project
{
private:
	int ID;
	static int lastID;
	string name;
	string type;
	Client* client;
	double cost;
	Date deadline;
	vector<Task*> tasks; //vector de tarefas;
	vector<Collaborator*> collaborators; //vector de colaboradores;
public:
	 
	//class de excep��o associada a Projectos
	class ProjectExcept
	{
		string description;
	public:
		ProjectExcept(string description) :description(description){};
		string operator()(){ return description; };
	};
	//class de compara��o geral
	class ProjectComparator
	{
	public:
		virtual bool operator()(const Project& t1, const Project& t2)=0;
	};
	//class de compara��o que servir� para ordenar os projectos de forma alfabetica
	class ProjectComparatorAlphabetic : public ProjectComparator
	{
	public:
		bool operator()(const Project& t1, const Project& t2) { return t1.name < t2.name; };
	};
	//class de compara��o que servir� para ordenar os projectos em fun��o do custo
	class ProjectComparatorCost : public ProjectComparator
	{
	public:
		bool operator()(const Project& t1, const Project& t2) { return t1.cost < t2.cost; };
	};
	//class de compara��o que servir� para ordenar os projectos em do seu ID
	class ProjectComparatorID : public ProjectComparator
	{
	public:
		bool operator()(const Project& t1, const Project& t2) { return t1.getID() < t2.getID(); };
	};
	Project() : ID(0), client(NULL), cost(0) {};
	Project(string name, string type, Date deadline, double cost ) : deadline(deadline), name(name), type(type), ID(++lastID), cost(cost){};
	Project(string name, string type, Date deadline, double cost, int setID) : name(name), type(type), ID(++lastID), deadline(deadline), cost(cost){ if (setID > lastID) lastID = setID; };
	Project(int i);
	int getID() const		{ return this->ID; };
	static int getLastID()  { return lastID; };
	string getName() const	{ return this->name; };
	string getType() const  { return this->type; };
	Client* getClient()	{ return this->client; };
	int getCost() const	{ return this->cost; };
	Date getDeadline()const { return deadline; };
	vector<Task*> getTasks() const { return this->tasks; };
	vector<Collaborator*> getCollaborators() const { return this->collaborators; };
	void setID(int ID) { this->ID = ID; };
	static void setLastID(int lID) { lastID = lID; };
	void setClient(Client* c, bool addProject = true);
	void setName(string newname){ name = newname; };
	void setType(string newtype){ type = newtype; };
	bool addCollaborator(Collaborator* c, bool addProject = true); //fun��o que adiciona colaboradores
	void addTask(Task * t, bool setProject = true);//fun��o que adiciona tarefas
	bool tick(); //calculo do custo do projecto;
	bool isCompleted(); //indica acerca da conclusao do projecto
	void connect();

	bool removeTask(Task* t, bool removeProject = true);

	bool operator==(const Project& p2) const { return (this->ID) == (p2.ID); };
	friend ostream & operator<<(ostream& out, const Project& p);
	friend istream & operator>>(istream& in, Project& p);
	
};
#endif
