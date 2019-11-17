
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 3: This project holds is a Hash table ADT that holds information on websites
// and is implemented using a Hash Table ADT and array data structure
// File Name: project3.cpp
/************************************/



#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "hashtable.h"
#include "website.h"

#define MYFILE "data.txt"
#define MAX_CHAR 201

using namespace std;

void displayMenu(); // Has the menu for users
char getCmd(); // gets the command from the user input
void processCmd(char cmd); // this processes the command from the user

void loadFile(const char* fileName);// Function loads the file for the hash table
//void loadTable (ifstream inputFile); // load data into the hash table

void insert();
void retrieve();
void edit();
void remove();
void display();
void displayAll();


static HashTable hashTable;


int main()
{
	loadFile(MYFILE);
	
	char cmd;
	
//	hashTable.displayAll(); // this displays the website list for testing
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



// Functiion works on a file expecting unix style new line characters ('\n')
void loadFile(const char* filename)
{
	// Loads the file - open file to read in data
	ifstream inputFile;
	inputFile.open(filename);
	if(inputFile.is_open())
	{
		cout << "Welcome to Website Hashtable Fun time... Successfully opened " << filename << endl;
		//loadQueue(&inputFile)
			
		char readline[MAX_CHAR];

		inputFile.getline(readline, MAX_CHAR );    // Get the whole next line of the file
		while (strcmp(readline,"") != 0)
		{
			// cout << "Readline is:" << readline << endl;
			char* topicName;
			char* websiteAddress;
			char* summary;
			char* review;
			int rating;

			topicName = strtok(readline, ";"); // From the line read, make a substring that goes until ";" is found
			websiteAddress = strtok(NULL, ";");
			summary = strtok(NULL, ";");
			review = strtok(NULL, ";");
			rating = atoi(strtok(NULL, ";")); // atoi converts the char to an int
			
			
			Website* w = new Website(topicName, websiteAddress, summary, review, rating);
			// cout << "Adding to hash table: " <<
				// topicName << " " <<
				// websiteAddress << " " <<
				// summary << " " <<
				// review << " " <<
				// rating << endl;
			hashTable.addWebsite(w);
			// cout << "Add okay!\n";
			
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
        cout << "Website Hashtable v1.0! Menu choices - Pick a Letter:" << endl
		<< "a.	Insert a new website into the hash table" << endl
		<< "b.	Retrieve all websites based on the topic keyword supplied" << endl
		<< "c.	Edit (modify the review and rating for a particular topic and website match)" << endl
		<< "d.	Remove (remove all websites with a 1 star rating)" << endl
		<< "e.	Display (only displaying matches, based on the topic keyword)" << endl
		<< "f.	Display all" << endl
        << "q. Quit" << endl;
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
		case 'a':       //add a website into the table
			insert();
		break;

		case 'b':
			retrieve(); // search for a website based on topic
		break;

		case 'c':
			edit(); // Edit a website
		break;

		case 'd':
			remove(); // remove websites that are rated 1 star
		break;

		case 'e':
			display(); // display a website
		break;

		case 'f':
			displayAll(); //display all websites
		break;

	}
}


// This function inserts a new website into the hash table. It also calls several otheyr functions to receive in the data.
void insert()
{
	char topicName[MAX_CHAR];
	char websiteAddress[MAX_CHAR];
	char summary[MAX_CHAR];
	char review[MAX_CHAR];
	char rating_char[MAX_CHAR];
	int rating;
	bool goodRating = false;

	cout << "Enter the topic name of the website: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	cout << "Enter the website address: ";
	cin.get(websiteAddress, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	cout << "Enter the summary of the website: ";
	cin.get(summary, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	
	cout << "Enter the review of the website: ";
	cin.get(review, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	
	while (goodRating == false)
	{
		cout << "Enter the rating (1 to 5) of the website: ";
		cin.get(rating_char, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		
		rating = atoi(rating_char);
		
		if (rating >= 1 && rating <= 5)
		{
			goodRating = true;
		}
	}
	
	Website* w = new Website(topicName, websiteAddress, summary, review, rating);
	hashTable.addWebsite(w);
	cout << "Successfully added a new website." << endl;
}


// This function retrieves a website by the user giving a topic name and searches the hashtable for a match
void retrieve()
{
	char topicName[MAX_CHAR];
	
	cout << "Enter the topic name of the website: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	
	Website matches[20];
	
	int count = hashTable.retrieve(topicName, matches, 20);
	cout << "Found " << count << " results in the topic.\n";
	
	for (int i = 0; i < count; ++i)
	{
		cout << "Retrieved data " << (i+1) << ": \n";
		Website* current = &matches[i];

		cout << current->getTopic() << " ";
		cout << current->getWebsiteAddress() << " ";
		cout << current->getSummary() << " ";
		cout << current->getReview() << " ";
		cout << current->getRating() << endl;
	
	}
}


// This function allows a user to edit a website by looking it up based on the topic name and address, then can put in a new reveiw and rating
void edit()
{
	char topicName[MAX_CHAR];
	char websiteAddress[MAX_CHAR];
	char review[MAX_CHAR];
	char rating_char[MAX_CHAR];
	int rating;
	bool goodRating = false;
	
	cout << "Enter the topic name of the website: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	
	cout << "Enter the website address: ";
	cin.get(websiteAddress, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	
	cout << "Enter the new review of the website: ";
	cin.get(review, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	
	while (goodRating == false)
	{
		cout << "Enter the rating (1 to 5) of the website: ";
		cin.get(rating_char, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		
		rating = atoi(rating_char);
		
		if (rating >= 1 && rating <= 5)
		{
			goodRating = true;
		}
	}
	
	bool foundWebsite = hashTable.editWebsite(topicName, websiteAddress, review, rating);
	
	if (foundWebsite == true)
	{
		cout << "Successfully updated review and rating for website\n";
	}
	else
	{
		cout << "Could not find website with topic " << topicName << " and address " << websiteAddress << endl;
	}
}


// This function calls removeWebsite which ermoves a website if it has a rating of 1
void remove()
{
	int count = hashTable.removeWebsite();
	cout << count << " websites removed (rated at 1 star)" << endl;
}


// This function displays a website by entering a topic name
void display()
{
	char topicName[MAX_CHAR];
	
	cout << "Enter the topic name of the website: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	
	hashTable.display(topicName);
}


// This function displays all the contents of the hashtable
void displayAll()
{
	hashTable.displayAll();
}

