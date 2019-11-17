/**********/
// Author: Giselle Northy
// Date: 10/28/2019
// Class Number: CS260
// Program Number: Project 2
// Purpose: Restaurant waiting list program that keeps track of guest list in a queue and if a customer wants promotional material, the program pushes names to the stack
// Name and Purpose of this file: project2.cpp, this serves as the main testing file for the project
/**********/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "stack.h"
#include "queue.h"

#define MYFILE2 "waitlist.txt"
#define MYFILE "promo.txt"
#define MAX_CHAR 101

using namespace std;

// defining prototypes
void displayMenu(); // Has the menu for users
char getCmd(); // gets the command from the user input
void processCmd(char cmd); // this processes the command from the user
void addGroup(); // works with enqueue function
void sitGroup();//  works with dequeue function
void displayList(); // works with display function
void showTop();
void getPromo(); // when we pop the person off the stack for the promo material
void saveList();
void loadFile(const char* fileName);// Function loads the file for the queue// Function loads the file for the queue
void loadQueue (ifstream inputFile); // loads the queue



static Queue waitList; // queue waiting list
static Stack promoList; // stack promo list

// main function
int main()
{
        loadFile(MYFILE2);

        char cmd;
        // MENU
        // Purpose is to start the user menu. Accepts char cmd's
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
                cout << "Welcome to Waiting list... Successfully opened " << filename << endl;
                //loadQueue(&inputFile)

    char readline[MAX_CHAR];

            inputFile.getline(readline, MAX_CHAR );    // Get the whole next line of the file
    while (strcmp(readline,"") != 0)
    {
		char* groupName;
		char* size;
		char* accom;
		bool accomodations;
		char* accomDetails;
	    char* wantPromo;
	    char* fullName;
	    char* email;

		groupName = strtok(readline, ";");    // From the line read, make a substring that goes until ";" is found
		size = strtok(NULL, ";");    // from where we were last in readline (current buffer), get a substring that goes until the next ";" is found
		accom = strtok(NULL, ";");    // from where we were last in readline (current buffer), get a substring that goes until the next ";" is found

		if(strcmp(accom, "1") == 0)
		{
			accomDetails = strtok(NULL, ";");
			 //   waitList.enqueue(groupName, atoi(size), true, accomDetails);
			accomodations = true;
		}
		else
		{
			  //  waitList.enqueue(groupName, atoi(size), false, nullptr);
			strtok(NULL, ";");
			accomodations = false;
			accomDetails = nullptr;
		}

		wantPromo = strtok(NULL, ";");
		if (strcmp(wantPromo, "1") == 0)
		{
			fullName = strtok(NULL, ";");
			email = strtok(NULL, ";");
			Person* p = new Person(fullName, email);

			waitList.enqueue(groupName, atoi(size), accomodations, accomDetails, true, p); 
		}
		else
		{
			waitList.enqueue(groupName, atoi(size), accomodations, accomDetails, false, nullptr); 

		}

            inputFile.getline(readline, MAX_CHAR );    // Get the whole next line of the file
         }
         inputFile.close();

        }
        else
        {
                cout << "Error, could not open file " << filename << " for reading.\n";
        }
}       // END loaded file



// Load queue reads the file to load it into the program
void loadQueue (ifstream inputFile)
{
}

// Displays the menu to the user
void displayMenu() // Has the menu for users
{
        cout << "Resturaunt Queue Happy fun time! Menu choices - Pick a Letter:" << endl
        << "a. Add a group to the waitlist." << endl // push
        << "b. Show the entire waitlist." << endl // display the list
        << "c. Show the top of the waitlist." << endl // peek
        << "d. Seat a group - dequeue & add to stack if promo = true." << endl
	<< "e. Send out the top promo contact." << endl // get next promo
        << "f. Save the waiting list to the file." << endl // save the waitlist to the file
        << "q. Quit" << endl;
}


// Function gets the command from the user
char getCmd() // gets the command from the user input
{
        char cmd;
        cin >> cmd;
        cin.ignore(MAX_CHAR, '\n');
        return tolower(cmd);
}



//
void processCmd(char cmd) // this processes the command from the user
{
        switch(cmd)
        {
                case 'a':       //add a a group to the waitlist
                        addGroup();
                break;

                case 'b':
                        displayList(); // show the waitlist
                break;

                case 'c':
                        showTop(); // shows the top of the list like peek
                break;

                case 'd':
                        sitGroup(); // add a function to seat the group
                break;

                case 'e':
                        getPromo(); // get the promo
                break;
		
		case 'f':
			saveList(); //save list to file

        }
}

/*
  << "a. Add a group to the waitlist." << endl // push
        << "b. Show the entire waitlist." << endl // display the list
        << "c. Show the top of the waitlist." << endl // peek
        << "d. Seat a group - dequeue & add to stack if promo = true." << endl
        << "e. Send out the top promo contact." << endl // get next promo
        << "f. Save the waiting list to the file." << end
*/


// This function adds groups to the file
void addGroup() // works with enqueue function
{
        char groupName[MAX_CHAR];
        char sizeChar[MAX_CHAR];
        int size;
        char groupAccom[MAX_CHAR];
        char accomDetail[MAX_CHAR];
	char* accomDetails;
        char promoInterest[MAX_CHAR];
	bool accomodations;

        cout << "Enter the name of the group: ";
        cin.get(groupName, MAX_CHAR, '\n');
        cin.ignore(100, '\n');

        cout << "Enter the size of the party: ";
        cin.get(sizeChar, MAX_CHAR, '\n');
        cin.ignore(100, '\n');
        size = atoi(sizeChar);

        cout << "Does ths group require special accommodations? (Y/N): ";
        cin.get(groupAccom, MAX_CHAR, '\n');
        cin.ignore(100, '\n');

        if (tolower(groupAccom[0]) == 'y')
        {
                cout << "What are the special accommodations?: ";
                cin.get(accomDetail, MAX_CHAR, '\n');
                cin.ignore(100, '\n');

		accomodations = true;
		accomDetails = accomDetail;
//                waitList.enqueue(groupName, size, true, accomDetail);
        }
        else
        {
		accomodations = false;
		accomDetails = nullptr;
//                waitList.enqueue(groupName, size, false, nullptr);
        }

        cout << "Would anyone be interested in receiving promotional material? (Y/N): ";
        cin.get(promoInterest, MAX_CHAR, '\n');
        cin.ignore(100, '\n');

	bool wantPromo = false;
        Person* p = nullptr;

        if (tolower(promoInterest[0]) == 'y')
        {
		wantPromo = true;
                char fullName[MAX_CHAR];
                char email[MAX_CHAR];

                cout << "Please enter your full name: ";
                cin.get(fullName, MAX_CHAR, '\n');
                cin.ignore(100, '\n');

                cout << "Enter your email address: ";
                cin.get(email, MAX_CHAR, '\n');
                cin.ignore(100, '\n');

                p = new Person(fullName, email);

		// we will be doing this when we go and sit the group instead
               // promoList.push(p);


             //   cout << "Would anyone else be interested in receiving promotional material? (Y/N): ";
             //   cin.get(promoInterest, MAX_CHAR, '\n');
             //   cin.ignore(100, '\n');

        }

	waitList.enqueue(groupName, size, accomodations, accomDetails, wantPromo, p);
}


// this function dequeues people so they sit
void sitGroup()//  works with dequeue function
{
	if (waitList.sizeOfQueue() > 0)
	{
		Group sitGroup;
		waitList.dequeue(sitGroup);
		cout << "Now sitting "; 
		cout << sitGroup.getName() << ", party of " << sitGroup.getSize() << endl;

		if(sitGroup.wantsPromo() == true)
		{
		  cout << "Adding contact info to promo list: Name " << sitGroup.getPromoContact()->getName() << " Email: " << sitGroup.getPromoContact()->getEmail()  << "\n";
			Person* p = new Person();
			*p = *sitGroup.getPromoContact();

			promoList.push(p);
		}	
	}
	else
	{
		cout << "There are no groups in the queue to sit\n";
	}
}


// this function shows who is on top
void showTop()
{
        Group* nextGroup;
        bool success = waitList.peek(nextGroup);

        if (success)
        {

                cout << "The next group on the list is " << nextGroup->getName() << ", party of " << nextGroup->getSize();
                if (nextGroup->getAccom() == true)
                {
                        cout << ", with the accommodations of " << nextGroup->getAccomDetails() << endl;
                }
                else
                {
                        cout << " with no special accommodations" << endl;
                }
        }
        else
        {
                cout << "The waiting list is currently empty\n";
        }
}



void displayList() // works with display function
{
//      bool foundGroup = false;

        waitList.display();
        promoList.display();

/*      char groupName[MAX_CHAR];

        while (groupName != false)
        {
                foundGroup = groupName.displayList(groupName);
        if (foundGroup == false)
        {
                cout << "No groups in the queue.\n";
        }
*/
}



void getPromo() // when we pop the person off the stack for the promo material
{
        Person p;
        // POP POP!
        bool success = promoList.pop(p);

        // save popped data to file
        if (success == true)
        {
	  cout << "Name: " << p.getName() << "\nEmail: " << p.getEmail() << "\n";

                ofstream file;
                file.open(MYFILE, ios_base::app);
                file << p.getName() << ";" << p.getEmail() << ";\n";
                file.close();
        }
}


// this function saves the list
void saveList()
{
        ofstream file;
        file.open(MYFILE2);
        waitList.writeInfo(file);
        file.close();
}


