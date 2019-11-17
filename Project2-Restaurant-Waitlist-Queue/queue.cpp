/**********/
// Author: Giselle Northy
// Date: 10/28/2019
// Class Number: CS260
// Program Number: Project 2
// Purpose: Restaurant waiting list program that keeps track of guest list in a queue and if a customer wants promotional material, the program pushes names to the stack
// Name and Purpose of this file: queue.cpp
/**********/

#include "queue.h"

// Constructor function initializes front and rear ptrs to null and size to 0
Queue::Queue(): front(nullptr), rear(nullptr), size(0)
{
}



// Destructor function destroys front and rear ptrs and sets to null
Queue::~Queue()
{
  if (front != nullptr)
  {
        destroy(front->next);
	if (size > 0)
	{
	    delete front->data;
	    delete front;
	}
	front = nullptr;
	rear = nullptr;
  }
}



// Destroy Recursive function destroys nodes and burninates villages
void Queue::destroy(Node *& currHead)
{
  //if(currHead->next != front)

	if(currHead != front)
	{
		destroy(currHead->next);
		delete currHead->data; // is data the correct thing here?
		delete currHead;
	}
}



// Enqueue function sets the people pointers
// The queue should be implemented using a circular linked list of people, where the rear pointer points to the most recent group to arrive at the restaurant, and rear->next points to the first group to arrive that hasn’t yet been seated.
void Queue::enqueue(char* name, int s, bool accom, char* accomDetails, bool wantPromo, Person* p)
{
	Group* newGroup = new Group(name, s, accom, accomDetails, wantPromo, p); // initializing a new group

	Node * newNode = new Node(newGroup);
	if (!rear)
	{	
		front = newNode;
		rear = newNode;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}
	rear->next = front; // set the rear pointing to the front
	size++;
}



// Dequeue function removes person at the front of the queue
bool Queue::dequeue(Group& aGroup)
{
	if(size == 0)
	{
		return false;
	}
	Node * temp = front;
	front = front->next;
	rear->next = front;
	aGroup = *(temp->data);
	delete temp->data;
	delete temp;
	size--;
	if (size == 0)
	{
	  front = nullptr;
	  rear = nullptr;
	}
	return true;
}




// Peek function shows the top of the queue
bool Queue::peek(Group *& aGroup) const // shows top of queue
{
	if(size != 0)
	{
		aGroup = front->data; // returns a ptr
		return true;
	}
	return false;
}



// Write Info function writes data to the external data text file
void Queue::writeInfo(ofstream & outputFile)
{
	Node* currPtr = front;
	bool doneLooping = false;

	while(doneLooping == false)
	{
		outputFile << currPtr->data->getName() << ";" << 
		currPtr->data->getSize() << ";" <<
		currPtr->data->getAccom() << ";"; // gets the name
		if(currPtr->data->getAccom() == true) // checking if accom is true or false
		{
			outputFile << currPtr->data->getAccomDetails() << ";";
		}
		else
		{
			outputFile << " " << ";";
		}
		outputFile << currPtr->data->wantsPromo() << ";";
		if(currPtr->data->wantsPromo() == true)
		{
		  outputFile << currPtr->data->getPromoContact()->getName() << ";" << currPtr->data->getPromoContact()->getEmail() << ";";
		}
		outputFile << "\n";
		if(currPtr->next == front)
		{
			doneLooping = true;
		}
		currPtr = currPtr->next;
	}
}


// Display function diplays the contents of the queue
void Queue::display() const
{
	int i = 1;
	for (Node * curr = front; curr; ++i)
	{
		cout << i << " " << curr->data->getName() << " " << curr->data->getSize() << " " <<
		curr->data->getAccom();
		if(curr->data->getAccom() == true)
		{
			cout << " " << curr->data->getAccomDetails();
		}
		cout << " " << curr->data->wantsPromo();
		if(curr->data->wantsPromo() == true)
		{
		  cout << " " << curr->data->getPromoContact()->getName() << " " << curr->data->getPromoContact()->getEmail();
		}
		cout << endl;
		if(curr->next == front)
		{
			curr = nullptr;
		}
		else
		{
			curr = curr->next;
		}
	}	
}


int Queue::sizeOfQueue()
{
	return size;
}



