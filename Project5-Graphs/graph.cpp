
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 5: This project is a Simple directed graph abstraction that stores tasks
// that need to be completed.
// File Name: graph.cpp
/************************************/


#include "graph.h"
#include <iostream>
#include <algorithm>


using namespace std;

// Constructor
Graph::Graph(int initArraySize)
{
	vertices = new Adjacent*[initArraySize];
	for (int i = 0; i < initArraySize; ++i)
	{
		vertices[i] = nullptr;
	}
	arraySize = 0;
	capacity = initArraySize;
}



// Destructor
Graph::~Graph()
{
	// clear out the vector and stack
	visited.clear();
	while(nodes.empty() == false)
	{
		nodes.pop();
	}

	// Go through the array and delete everything
	for(int i = 0; i < arraySize; ++i)
	{
		destroy(vertices[i]->head);
		delete(vertices[i]->task);
		delete(vertices[i]);
	}
	delete[] vertices;

}



// recursively delete the linked lists
void Graph::destroy(EdgeNode*& current)
{
	if (current != nullptr)
	{
		destroy(current->next);
		delete(current);
		current = nullptr;
	}
}



// Loading data in from a file, puts in a new task into the array
void Graph::addNewTask(char* task)
{
	int i = 0;
	// cout << "in addNewTask for " << task << endl;
	bool found = findTask(task, i);
	// don't add a task that is already in there
	if (found == false)
	{
		// check if there is room in the array for a new one
		if (arraySize == capacity)
		{
			growArray();	// Make array bigger
		}

		// Create new element for array
		Vertex* v = new Vertex(task);
		Adjacent* a = new Adjacent;
		a->task = v;
		a->head = nullptr;

		vertices[arraySize] = a;
		++arraySize;

	}
}



// Loading data in from a file, puts a new adjacent task into an existing task.
// if existingTask cannot be found, the function returns false and does not complete
// if adjacent task does not exist yet, it will create it.
bool Graph::addNewAdjacentTask(char* existingTask, char* adjacentTask)
{
	bool found = false;
	int existingIndex = 0;
	int adjacentIndex = 0;

	// see if it can find the existingTask
	found = findTask(existingTask, existingIndex);

	// see if it can find the adjacentTask
	if(findTask(adjacentTask, adjacentIndex) == false)
	{
		// Create new task if adjacent task not found
		addNewTask(adjacentTask);
		// update index for insertion
		findTask(adjacentTask, adjacentIndex);
	}

	if (found == true)
	{
		// Make new element in linear linked list of adjacent tasks
		EdgeNode* e = new EdgeNode;
		e->adjacentTask = vertices[adjacentIndex];
		e->next = vertices[existingIndex]->head;
		vertices[existingIndex]->head = e;
	}

	return found;
}



// Looks through the existing tasks to see if one matches the char* task parameter
// If so, it updates the index passed by reference to where it is in the array
bool Graph::findTask(char* task, int& index)
{
	bool found = false;
	for (int i = 0; i < arraySize; ++i)
	{
		if (strcmp(vertices[i]->task->getTaskInfo(), task) == 0)
		{
			found = true;
			index = i;
			break;
		}
	}

	return found;
}


// Display all other tasks that need to get done once this task has been complete.
// Using recursion to do this.
void Graph::displayTasksAfterThisOne(char* task)
{
	int index = 0;
	bool found = findTask(task, index);
	if (found == true)
	{
		cout << "Current Task: " << vertices[index]->task->getTaskInfo() << " has the remaining tasks after it:" << endl;

		displayEdgeTasks(vertices[index]->head);
	}
	else
	{
		cout << "Could not find that task" << endl;
	}
}



// Recursive call coming from displayTasksAfterThisOne
void Graph::displayEdgeTasks(EdgeNode* current)
{
	if (current)
	{
		cout << "  " << current->adjacentTask->task->getTaskInfo() << endl;
		displayEdgeTasks(current->next);
	}
}



// given a starting task, performs depth first traversal to show all connected tasks
// returns false if unable to find the given starting task
bool Graph::depthFirstTraversal(char* task)
{
	int index = 0;
	bool found = findTask(task, index);
	if (found == true)
	{
		// Clear out the vector and stack
		visited.clear();
		while(nodes.empty() == false)
		{
			nodes.pop();
		}
		// need to keep track of vertices already visited
		visited.push_back(vertices[index]);
		// keep track of path, where to go next
		nodes.push(vertices[index]);
		cout << vertices[index]->task->getTaskInfo() << endl;
		// recursive call to depth
		depthTraversal(vertices[index]->head);

		// see if we have any more nodes left
		Adjacent* next;
		while (nodes.empty() == false)
		{
			next = nodes.top();
			nodes.pop();
			depthTraversal(next->head);
		}

	}
	return found;
}



// This function is the depth first traversal recursion call to linked list
void Graph::depthTraversal(EdgeNode* current)
{
	// find next adjacent node that hasn't been visited
	if(current != nullptr)
	{
		// make sure this one has not been already visited
		if (find(visited.begin(), visited.end(), current->adjacentTask) == visited.end())
		{
			visited.push_back(current->adjacentTask);
			nodes.push(current->adjacentTask);
			cout << current->adjacentTask->task->getTaskInfo() << endl;
			depthTraversal(current->adjacentTask->head);

			// call next adjacent node when the previous depth call is done
			depthTraversal(current->next);
		}
		else
		{
			// element already visted, check next one
			depthTraversal(current->next);
		}
	}
	else
	{
		// finished this adjacent node
		nodes.pop();
	}
}



// This function is used if the array needs to be resized
void Graph::growArray()
{
	// make new array
	Adjacent** newVertices = new Adjacent*[capacity*capacityGrowth];

	// copy elements into new array
	for(int i = 0; i < arraySize; ++i)
	{
		newVertices[i] = vertices[i];
	}

	// delete old array
	delete[] vertices;

	// update pointer
	vertices = newVertices;
}
