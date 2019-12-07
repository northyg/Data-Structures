
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 5: This project is a Simple directed graph abstraction that stores tasks
// that need to be completed.
// File Name: project5.cpp
/************************************/



#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "graph.h"


#define MYFILE "data.txt"
#define MAX_CHAR 201

using namespace std;

void displayMenu(); // Has the menu for users
char getCmd(); // gets the command from the user input
void processCmd(char cmd); // this processes the command from the user

void loadFile(const char* fileName);// Function loads the file for the hash table

void insert();
void retrieve();
void edit();
void remove();
void display();
void depthTraverse();


static Graph graph(10);


// main function loads the data file and starts the menu
int main()
{
	loadFile(MYFILE);

	char cmd;

	displayMenu();
	cmd = getCmd();

	while (cmd != 'q')
	{
		processCmd(cmd);
        displayMenu();
        cmd = getCmd();
	}
	return 0;
}



// Function works on a file expecting unix style new line characters ('\n')
void loadFile(const char* filename)
{
	// Loads the file - open file to read in data
	ifstream inputFile;
	inputFile.open(filename);
	if(inputFile.is_open())
	{
		cout << "Welcome to Graph Fun time. The tasks added are below. Successfully opened " << filename << endl;
		//loadQueue(&inputFile)

		char readline[MAX_CHAR];

		inputFile.getline(readline, MAX_CHAR );    // Get the whole next line of the file
		while (strcmp(readline,"") != 0)
		{
			cout << "Readline is:" << readline << endl;
			char* taskName;
			char* subTask;

			taskName = strtok(readline, ";"); // From the line read, make a substring that goes until ";" is found
			cout << "adding " << taskName << " to graph..." << endl;
			graph.addNewTask(taskName);

			subTask = strtok(NULL, ";");
			while((subTask != NULL) && (strlen(subTask) !=1))
			{
				cout << "adding " << subTask << " to next task..." << endl;
				graph.addNewAdjacentTask(taskName, subTask);
				subTask = strtok(NULL, ";");
			}
			inputFile.getline(readline, MAX_CHAR );    // Get the whole next line of the file
		}

		inputFile.close();
	}
	else
	{
			cout << "Error, could not open file " << filename << " for reading.\n";
	}
}



// This function displays the menu for users to test the functions
void displayMenu()
{
        cout << "Task Graph v1.0! Menu choices - Pick a Letter:" << endl
		<< "a.	Recursively displays all other tasks that need to get done once this task has been complete. User picks a task." << endl
		<< "b.	Depth First Traversal – show from start to end every path that needs to take place to make this event a success! User picks a task." << endl
    << "q.	Quit" << endl;
}



// Function gets the command from the user
char getCmd()
{
        char cmd;
        cin >> cmd;
        cin.ignore(MAX_CHAR, '\n');
        return tolower(cmd);
}


// Function processes the commands for the user using switch statements
void processCmd(char cmd)
{
	switch(cmd)
	{
		case 'a':       //display all other tasks that need to get done
			display();
		break;

		case 'b':
			depthTraverse(); // Depth first traverse
		break;
	}
}



// Recursively displays all other tasks that need to get done once this task
// has been complete. User picks a task.
void display()
{
	char topicName[MAX_CHAR];

	cout << "Enter the task to display later tasks for: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	graph.displayTasksAfterThisOne(topicName);
}



// This function Depth First Traversal – show from start to end every path that needs
//to take place to make this event a success! Use a combination of iteration and recursion
// to implement this algorithm!
void depthTraverse()
{
	char topicName[MAX_CHAR];

	cout << "Enter the task to depth traverse from: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	graph.depthFirstTraversal(topicName);
}
