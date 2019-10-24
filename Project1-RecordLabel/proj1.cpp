/*************************/
// Giselle Northy, 10/14/2019, Project1, test.cpp
// Description of what file contains (purpose): This program creates a list of artists
// that belong to a record label. Artists have songs associated with them. Users can
// add songs, remove songs and edit songs.
/*************************/


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "recordlabel.h"
#include "artist.h"

#define MYFILE "records.txt"
#define MYFILE2 "records.txt"
#define MAX_CHAR 101

using namespace std;

// defining prototypes
void displayMenu();
char getCmd();
void processCmd(char cmd, RecordLabel& editThing); 
void addSong(RecordLabel& recordLabel);
void addArtist(RecordLabel& recordLabel);
void editSong(RecordLabel& recordLabel);
void displaySongs(RecordLabel& recordLabel);
void removeSong(RecordLabel& recordLabel);



// Purpose is to read the text file and load the song and artist data
int main()
{	
	RecordLabel recordLabel;
	
	char readline[256];

	char cmd; // this is for the menu commands

	//Loads the file -  Opening file to read in data
	ifstream inputFile;
	inputFile.open(MYFILE);
	if(inputFile.is_open())
	{
		cout << "Welcome to Record Label...Sucessfully opened " << MYFILE << endl;
		
		while (inputFile.is_open())
		{
			inputFile.getline(readline, 256);
			if (strcmp(readline, "Artist:") == 0)
			{
				char* readdata = NULL;
				inputFile.getline(readline, 256);
				char* artistName;
				char* topStory;
				char* description;
				readdata = strtok(readline, ";");
				artistName = new char[strlen(readdata+1)];
				strcpy(artistName, readdata);
				topStory = strtok(NULL, ";");
				description = strtok(NULL, ";");
				
				// Artists added
				recordLabel.addArtist(artistName, topStory, description); 
				inputFile.getline(readline, 256);
				readdata = strtok(readline, ";");
				while((readdata != NULL) && (strlen(readdata) !=1))
				{
					char* songName = new char[strlen(readdata+1)];
					strcpy(songName, readdata);
					double length = atof(strtok(NULL, ";"));
					int views = atoi(strtok(NULL, ";"));
					int likes = atoi(strtok(NULL,";"));
					
					//This part used for testing songs added
					recordLabel.addSong(artistName, songName, length, views, likes);
					delete[] songName;

					inputFile.getline(readline, 256);
					readdata = strtok(readline, ";");
				}		
				delete[] artistName;
			}
			else
			{
				inputFile.close();
			}
		}

		inputFile.close();
	}
	else
	{
		cout << "Error, could not open file " << MYFILE << " for reading.\n";
	}

	// END Loaded File - After adding from the file
	


	// MENU
	// Purpose is to start the user menu. Accepts char cmd's
	displayMenu();
	cmd = getCmd();

	while (cmd != 'q')
	{
		processCmd(cmd, recordLabel);
		displayMenu();
		cmd = getCmd();
	}

	// called display artists for testing
	// recordLabel.displayArtists();
	ofstream outputFile;
	outputFile.open(MYFILE2);

	recordLabel.unLoadData(outputFile); // write the data back to the file
	outputFile.close();

	return 0;
} 
// end of main()



//Purpose is to ask user what they would like to do with the artists and songs. Accepts CHAR
void displayMenu()
{
	cout << "Menu choices - Pick a Letter:" << endl
	<< "a. Add a new artist." << endl
	<< "b. Add a new song for an artist." << endl
	<< "c. Edit # of views and likes for a song." << endl
	<< "d. Display all songs for an artist." << endl
	<< "e. Display all artists." << endl
	<< "f. Remove songs w/ fewer than 'M' views, user inputs M." << endl
	<< "q. Quit" << endl;
}



// Purpose is to retrieve a single character input from the user
char getCmd()
{
	char cmd;
	cin >> cmd;
	cin.ignore(MAX_CHAR, '\n');
	return tolower(cmd);
}



// Purpose is to process the given user input and performs the necessary action
void processCmd(char cmd, RecordLabel& editThing) 
{
	switch(cmd)
	{
		case 'a':	//add an artist
			addArtist(editThing);
		break;

		case 'b':	//add new song for an artist
			addSong(editThing);
		break;

		case 'c':	// edit number of views and likes for  song
			editSong(editThing);
		break;

		case 'd': 	// display all songs for an artist in order of greatest to least likes
			displaySongs(editThing);
		break;

		case 'e':	// display all aritsts
			editThing.displayArtists();
		break;

		case 'f':	// remove songs based on M views
			removeSong(editThing);
		break;
	}
}



// Purpose is to add the artist. Takes in CHAR's for the name
void addArtist(RecordLabel& recordLabel)
{
	bool artistAddedSuccessfully = false;
	char name[MAX_CHAR];
	char topStory[MAX_CHAR];
	char description[MAX_CHAR];
	
	while (artistAddedSuccessfully == false)
	{
		// Ask user for the name of the new arist
		cout << "Enter a name for the new artist: ";
		cin.get(name, MAX_CHAR, '\n');
		cin.ignore(100, '\n');	// to throw away the new line character

		// Ask user for the top story of the artist
		cout << "Enter a top story for the artist: ";
		cin.get(topStory, MAX_CHAR, '\n');
		cin.ignore(100, '\n');

		// Ask user for the description of the arist
		cout << "Enter a description for the artist: ";
		cin.get(description, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
	
		// Attempt to add the artist
		artistAddedSuccessfully = recordLabel.addArtist(name, topStory, description);
		
		if (artistAddedSuccessfully == true)
		{
			cout << "Artist added succesfully\n";	
		}
		else
		{
			cout << "That artist already exists, please enter a new artist.\n";
		}
	}
}	



// Purpose is to add songs to an artist. 
void addSong(RecordLabel& recordLabel)
{
	bool songAddedSuccessfully = false;
	char artistName[MAX_CHAR];
	char songName[MAX_CHAR];
	char length[MAX_CHAR];
	char views[MAX_CHAR];
	char likes[MAX_CHAR];
	double lengthConverted;
	int viewsConverted;
	int likesConverted;

	// this code adds a song
	
	while (songAddedSuccessfully == false)
	{
		// Ask user for name of song artist
		cout << "Enter an artist name to add a song to: ";
		cin.get(artistName, MAX_CHAR, '\n');
		cin.ignore(100, '\n');

		// Ask user for the song name
		cout << "Enter a name for the new song: ";
		cin.get(songName, MAX_CHAR, '\n');
		cin.ignore(100, '\n');

		// Ask user for the song length
		cout << "Enter the song length in double: ";
		cin.get(length, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		lengthConverted = atof(length); // convert char to double
		
		// Ask user for number of views
		cout << "Enter the number of song views in int: ";
		cin.get(views, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		viewsConverted = atoi(views); // convert char to int

		// Ask user for number of likes
		cout << "Enter the number of likes in int: ";
		cin.get(likes, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		likesConverted = atoi(likes); // convert char to int

		/* This was for testing 
		cout << "Artist name" << artistName << endl;
		cout << "Song name" << songName << endl;
		cout << "Length" << lengthConverted << endl;
		cout << "Views" << viewsConverted << endl;
		cout << "Likes converted" << likesConverted << endl;
		*/

		songAddedSuccessfully = recordLabel.addSong(artistName, songName, lengthConverted, viewsConverted, likesConverted);
		if (songAddedSuccessfully == true)
		{
			cout << "Song added sucessfully!\n";	
		}		
		else
		{	
			cout << "Did not add song, try again!\n";
		}
	
	}
}



// Purpose is to edit an existing song 
void editSong(RecordLabel& recordLabel)
{
	bool editSongSuccessfully = false;
	char artistName[MAX_CHAR];
	char songName[MAX_CHAR];
	char views[MAX_CHAR];
	char likes[MAX_CHAR];
	int viewsConverted;
	int likesConverted;
	
	while (editSongSuccessfully == false)
	{
		// Ask user for name of song artist
		cout << "Enter the artist name of the song you want to edit: ";
		cin.get(artistName, MAX_CHAR, '\n');
		cin.ignore(100, '\n');

		// Ask user for the song name
		cout << "Enter a name for the song to edit: ";
		cin.get(songName, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		
		// Commented out as editing the song length was not required
		/** Ask user for the song length
		cout << "Enter the song length in double: ";
		cin.get(length, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		lengthConverted = atof(length); // convert char to double**/
		
		// Ask user for number of views
		cout << "Enter the new number of song views in int: ";
		cin.get(views, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		viewsConverted = atoi(views); // convert char to int

		// Ask user for number of likes
		cout << "Enter the new number of likes in int: ";
		cin.get(likes, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
		likesConverted = atoi(likes); // convert char to int
	
		// Editing the song
		editSongSuccessfully = recordLabel.editSong(artistName, songName, viewsConverted, likesConverted);

		if (editSongSuccessfully == true)
		{
			cout << "Song edited sucessfully!\n";	
		}		
		else
		{	
			cout << "Could not find that artist or song.\n";
		}
	
	}
}



// Purpose is to display the songs for an artist that the user picks
void displaySongs(RecordLabel& recordLabel)
{
	bool foundArtist = false;
	char artistName[MAX_CHAR];
	
	while (foundArtist == false)
	{
		// Ask user for name of song artist
		cout << "Enter the artist you want to display songs for: ";
		cin.get(artistName, MAX_CHAR, '\n');
		cin.ignore(100, '\n');
	
		// Finding the artist
		foundArtist = recordLabel.displaySongs(artistName);

		if (foundArtist == false)
		{
			cout << "Could not find that artist.\n";
		}
	
	}

}



// Purpose is to remove a song with fewer than 'M' views. The user defines 'M'.
void removeSong(RecordLabel& recordLabel)
{
	//bool foundSongToRemove = false;
	char mViews[MAX_CHAR];
	int mConverted; // convert char to int

	cout << "This removes songs with less than 'M' views. Enter a value for 'M': ";
	cin.get(mViews, MAX_CHAR, '\n');
	cin.ignore(100, '\n');
	mConverted = atoi(mViews);

	int removed = recordLabel.removeSongs(mConverted);
	cout << removed << " songs were removed.\n";
}	

