#ifndef PROJECT_H
#define PROJECT_H


#include "Task.h"
#include "Collaborator.h"
#include "Client.h"
#include "Date.h"

#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Client;
class Task;
class Collaborator;

class Project
{
private:
	int ID;
	static int lastID;
	Date deadline;
	string name;
	string type;
	Client* client;
	int cost;
	vector<Task*> tasks;
	vector<Collaborator*> collaborators;
public:
	Project(Date deadline, string name, string type = "", Client* client = NULL, int id = Project::lastID) : deadline(deadline), name(name), type(type), client(client), ID(id){ if (id > lastID) lastID = id; };
	int getID() const		{ return this->ID; };
	static int getLastID()  { return lastID; };
	string getName() const	{ return this->name; };
	string getType() const  { return this->type; };
	Client* getClient()	{ return this->client; };
	int getCost() const	{ return this->cost; };
	vector<Task*> getTasks() const { return this->tasks; };
	vector<Collaborator*> getCollaborators() const { return this->collaborators; };
	int setID(int ID) { this->ID = ID; };
	static int setLastID(int lID) { lastID = lID; };
	bool operator==(const Project& p2) const { return this->ID == p2.ID; };
	void print() { cout << ID << name << type << client << cost; };
	


};
#endif