
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 4: This project utilizes a binary search tree (BST) to store
// websites and their info such as keyboard, rating, topic, summary and address
// File Name: project4.cpp
/************************************/



#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "bst.h"
#include "website.h"

#define MYFILE "data.txt"
#define MAX_CHAR 201

using namespace std;

void displayMenu(); // Has the menu for users
char getCmd(); // gets the command from the user input
void processCmd(char cmd); // this processes the command from the user

void loadFile(const char* fileName);// Function loads the file for the hash table
//void loadTable (ifstream inputFile); // load data into the hash table

void insert(); // insert website
void retrieve(); // retrieve website
void removeTopic(); // remove by topic
void removeKeyword(); // remove by keyword
void displayAll(); // display all websites
void displayHeight(); // display the height of tree


static BST bst; // static until end of program



// This loads the data file to populate the tree
int main()
{
	loadFile(MYFILE);

	char cmd;

// display the menu
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
		cout << "Welcome to Website BST Fun time... Successfully opened " << filename << endl;

		char readline[MAX_CHAR];

		inputFile.getline(readline, MAX_CHAR );    // Get the whole next line of the file
		while (strcmp(readline,"") != 0)
		{
			char* topicName;
			char* keyword;
			char* websiteAddress;
			char* summary;
			char* review;
			int rating;

			topicName = strtok(readline, ";"); // From the line read, make a substring that goes until ";" is found
			keyword = strtok(NULL, ";");
			websiteAddress = strtok(NULL, ";");
			summary = strtok(NULL, ";");
			review = strtok(NULL, ";");
			rating = atoi(strtok(NULL, ";")); // atoi converts the char to an int


			Website* w = new Website(topicName, keyword, websiteAddress, summary, review, rating);
			// cout << "Adding to hash table: " <<
				// topicName << " " <<
				// websiteAddress << " " <<
				// summary << " " <<
				// review << " " <<
				// rating << endl;
			bst.addWebsite(w);
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
        cout << "Website BST v1.0! Menu choices - Pick a Letter:" << endl
		<< "a.	Insert a new website into the BST" << endl
		<< "b.	Retrieve all websites based on the topic keyword supplied" << endl
		<< "c.	Remove Topics (Remove all matches for a particular topic)" << endl
		<< "d.	Remove Keyword (remove a specific website with the key word)" << endl
		<< "e.	Display all" << endl
		<< "f.	Display tree height" << endl
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
		case 'a':       //add a website into the BST
			insert();
		break;

		case 'b':
			retrieve();	 // search for a website based on topic
		break;

		case 'c':
			removeTopic();	 // Remove by topic
		break;

		case 'd':
			removeKeyword();	 // remove by keyword
		break;

		case 'e':
			displayAll(); 	//display all websites
		break;

		case 'f':
			displayHeight(); // display height of the tree
		break;

	}
}


// This function inserts a new website into the tree. It also calls several other functions to receive in the data.
void insert()
{
	char topicName[MAX_CHAR];
	char keyword[MAX_CHAR];
	char websiteAddress[MAX_CHAR];
	char summary[MAX_CHAR];
	char review[MAX_CHAR];
	char rating_char[MAX_CHAR];
	int rating;
	bool goodRating = false;

	cout << "Enter the topic name of the website: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	cout << "Enter the keyword: ";
	cin.get(keyword, MAX_CHAR, '\n');
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

	Website* w = new Website(topicName, keyword, websiteAddress, summary, review, rating);
	bst.addWebsite(w);
	cout << "Successfully added a new website." << endl;
}


// This function retrieves a website by the user giving a topic name and searches the BST for a match
void retrieve()
{
	char keyword[MAX_CHAR];

	cout << "Enter the keyword of the website: ";
	cin.get(keyword, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	Website* match;

	bool found = bst.retrieve(keyword, match);
	// cout << "Found " << count << " results in the topic.\n";

	if (found)
	{
		cout << "Found match: \n";
		Website* current = match;

		cout << current->getTopic() << " ";
		cout << current->getKeyword() << " ";
		cout << current->getWebsiteAddress() << " ";
		cout << current->getSummary() << " ";
		cout << current->getReview() << " ";
		cout << current->getRating() << endl;

	}
	else
	{
		cout << "Did not find match for that keyword\n";
	}
}



// This function calls removeWebsite which removes a website if it matches the topic
void removeTopic()
{
	char topicName[MAX_CHAR];

	cout << "Enter the topic name of the website: ";
	cin.get(topicName, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	int count = bst.removeWebsiteTopic(topicName);
	cout << count << " websites removed with that topic" << endl;
}



// This function removes a website based on a keyword
void removeKeyword()
{
	char keyword[MAX_CHAR];

	cout << "Enter the keyword of the website: ";
	cin.get(keyword, MAX_CHAR, '\n');
	cin.ignore(100, '\n');

	bool found = bst.removeWebsiteKeyWord(keyword); // remove one website based on a keyword

	if (found)
	{
		cout << "Removed site matching keyword: " << keyword << ": \n";
	}
	else
	{
		cout << "Could not find that website keyword to remove\n";
	}
}



// This function displays all the contents of the BST
void displayAll()
{
	bst.displayAll();
}



// This function displays the height of the BST
void displayHeight()
{
	cout << "Height of tree is: " << bst.getHeight() << endl;
}
