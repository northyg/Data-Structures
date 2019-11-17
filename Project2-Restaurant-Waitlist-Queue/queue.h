/**********/
// Author: Giselle Northy
// Date: 10/28/2019
// Class Number: CS260
// Program Number: Project 2
// Purpose: Restaurant waiting list program that keeps track of guest list in a queue and if a customer wants promotional material, the program pushes names to the stack
// Name and Purpose of this file: queue.h
/**********/

#ifndef QUEUE_H
#define QUEUE_H
#include "group.h"
#include <fstream>
#include <iostream>

using namespace std;

// class for the queue!
class Queue
{
public:
	Queue(); // constructor
	~Queue(); // destructor

	void enqueue(char* name, int size, bool accom, char* accomDetails, bool wantPromot, Person* p); // enqueue the people pointers
	bool dequeue(Group& aGroup); // removes person at front of queue
	bool peek(Group *& aGroup) const; // shows top of queue
	void writeInfo(ofstream & outputFile); // writes info to external file
	int sizeOfQueue();
	void display() const; // displays contents of queue

private:
	struct Node
	{
		Node(Group * g)
		{
			data = g;
			next = nullptr; // setting next to nullptr
		}
		Group * data;
		Node * next;
	};
	Node * front, *rear;
	int size; // size of the circular linked list

	void destroy(Node *& currHead); //think this is to destroy nodes
};	

#endif

