
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 5: This project is a Simple directed graph abstraction that stores tasks
// that need to be completed.
// File Name: vetex.h
/************************************/


#include <stdlib.h>
#include <cstdlib>
#include <cstring>


class Vertex
{
public:
	Vertex(); // default Constructor
	Vertex(char* task); // Constructor
	~Vertex(); // Destructor

	char* getTaskInfo(); // return task info
	void setTaskInfo(char* task); // set task info

private:
	char* taskInfo;


};
