
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 5: This project is a Simple directed graph abstraction that stores tasks
// that need to be completed.
// File Name: vertex.cpp
/************************************/

#include "vertex.h"
#include <iostream>


using namespace std;



// Default Constructor
Vertex::Vertex()
{
	taskInfo = nullptr;
}


// Constructor
Vertex::Vertex(char* task)
{
	taskInfo = strdup(task);
}



// Destructor
Vertex::~Vertex()
{
	if (taskInfo != nullptr)
	{
		free(taskInfo);
		taskInfo = nullptr;
	}
}



// return the task info
char* Vertex::getTaskInfo()
{
	return taskInfo;
}



// set the task info
void Vertex::setTaskInfo(char* task)
{
	if (taskInfo != nullptr)
	{
		free(taskInfo);
		taskInfo = nullptr;
	}

	taskInfo = strdup(task);
}
