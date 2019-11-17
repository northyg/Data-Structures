/**********/
// Author: Giselle Northy
// Date: 10/28/2019
// Class Number: CS260
// Program Number: Project 2
// Purpose: Restaurant waiting list program that keeps track of guest list in a 
//queue and if a customer wants promotional material, the program pushes names to the stack
// Name and Purpose of this file: stack.h 
/**********/

#ifndef STACK_H
#define STACK_H

#include <fstream>
#include <cstring>
#include <cstdlib>


using namespace std;

// order of headerfile stuff structures, classes, prototypes definitions

class Person
{
 public:
   Person();
   Person(char* fn, char* e);
   
   ~Person();
    
   char* getName();
   char* getEmail();

   void operator=(const Person &p);

private:
   char* fullName;
   char* email;
};

class Stack
{
public:
	Stack(); // assignment said receive the size of the array from the client program
	~Stack();

	void push(Person* aPerson); // pushes char arrays onto stack
	bool pop(Person& aPerson); // pops char array name & email off stack to be written to file 
	bool peek(Person *& aPerson); // shows the name of what is on the top of the stack
	void display(); // Shows the contents of the promo array - full name, email
private:
	Person ** aStack; // array of pointers
	int count; // number of elements in the stack
	static const int INITIAL_CAP = 10; // initial size of array
	static const int GROWTH_VALUE = 2; // multiplier for array growth
	int currCapacity; // current max size of the array
	void growStack(); // grows the stack size when it gets full
	void writeInfo(ofstream & outputFile); // function to write array to file 
};

#endif




