
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 5: This project is a Simple directed graph abstraction that stores tasks
// that need to be completed.
// File Name: graph.h
/************************************/



#include "vertex.h"
#include <vector>
#include <stack>

using namespace std;


class Graph
{
public:
	Graph(int initArraySize);
	~Graph();

	// Load in new data
	void addNewTask(char* task);	// Loading data in from a file, puts in a new task into the array
	bool addNewAdjacentTask(char* existingTask, char* adjacentTask);	// Loading data in from a file, puts a new adjacent task into an existing task. returns false if could not find existing task

	void displayTasksAfterThisOne(char* task); // Display all other tasks that need to get done once this task has been complete.

	bool depthFirstTraversal(char* task); // Depth First Traversal – show from start to end every path that needs to take place to make
	// this event a success! Use a combination of iteration and recursion

private:
	struct Adjacent;

	struct EdgeNode
	{
		Adjacent* adjacentTask;	//
		EdgeNode* next;
	};


	struct Adjacent
	{
		Vertex* task;
		EdgeNode* head;
	};

	Adjacent** vertices;
	int arraySize;
	int capacity;
	vector<Adjacent*> visited;
	stack<Adjacent*> nodes;

	const int capacityGrowth = 2;

	void destroy(EdgeNode*& current);
	bool findTask(char* task, int& index);
	void displayEdgeTasks(EdgeNode* current);
	void depthTraversal(EdgeNode* current);
	void growArray();	// resize array if needed
};
