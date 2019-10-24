/*************************/
// Giselle Northy, 10/14/2019, Project1, artist.cpp
// Description of what file contains (purpose): This program creates a list of artists
// that belong to a record label. Artists have songs associated with them. Users can
// add songs, remove songs and edit songs.
/*************************/

#include <cstring> // cstring library for strlen, strcpy & strcmp
#include <cstdlib> // for using free and deallocating strdup calls
#include <iostream> // for cout

#include "artist.h"

using namespace std;

// CODE ORDER should be: constructors, destructor. remaining member functions
// 3 spaces between functions


// Purpose is to construct an artist. It assigns head to null,
// name
Artist::Artist(char* n, char* ts, char* desc)
{
	head = nullptr;
	name = strdup(n); // this works on vim
	topStory = strdup(ts); // this works on vim
	description = strdup(desc); // this works on vim
}
	


// Purpose is as decronstructor and free the memory for name, topStory
// and description
Artist::~Artist()
{
	free(name);
	free(topStory);
	free(description);

	SongNode* curPtr = head;
	while(curPtr != nullptr)
	{
		SongNode* delPtr = curPtr;
		free(curPtr->title);
		curPtr = curPtr->next;
		delete delPtr;
	}
}


// Purpose is to return ptr to artist's name
char* Artist::getName()
{
	return name;
}


// Purpose is to add songs to artists. It inputs the song title,
// song length, song views and song likes
bool Artist::addSong(char* title, double length, int views, int likes)
{
	SongNode* newSongPtr = new SongNode; //assigns memory for a new song node
	newSongPtr->title = strdup(title);
	newSongPtr->length = length;
	newSongPtr->views = views;
	newSongPtr->likes = likes;

	// place new song into correct position in linked list
	insertSong(head, newSongPtr);
	return true;
}



// Purpose is to put song in recursively in the correct position
// input is the current node by reference to compare and update
// newSong is the new song to add. The songs are ordered by likes descending
void Artist::insertSong(SongNode *& current, SongNode* newSong)
{
	if((current == nullptr) || (newSong->likes >= current->likes))
	{
		newSong->next = current;
		current = newSong;
	}
	else
	{
		//recursive call to append to the smaller list
		insertSong(current->next, newSong);
	}
}



// Purpose is to edit songs. It takes int v which is views and
// int l which is likes
bool Artist::editSong(char* song, int v, int l)
{
	bool found = false;
	SongNode* curPtr = head;
	SongNode* prevPtr = nullptr;

	while(!found && (curPtr !=nullptr))
	{
		if (strcmp(song, curPtr->title) == 0) // return 0 if the contents of both strings are equal
		{
			found = true;
		}
		else
		{
			prevPtr = curPtr;
			curPtr = curPtr->next;
		}
	}
	if(found)
	{
		curPtr->views = v;
		curPtr->likes = l;
	
		// We are removing this from the list, then calling our
		// recursive function to re-add it into the correct spot	
		if(prevPtr == nullptr)
		{
			head = curPtr->next;
		}
		else
		{
			prevPtr->next = curPtr->next;
		}

		insertSong(head, curPtr);	// calling function to insert song to keep order
	}

	return found;
}



// Public function to kick off recursive call to display all songs
void Artist::displaySongs()
{
	displaySong(head);
}



// Purpose is to display songs. It displays a char* to the songs 
// of an artist
void Artist::displaySong(SongNode* song)
{
	if(song != nullptr)
	{
		cout << (song->title) << endl;
		displaySong(song->next);
	}
	else
	{
		cout << "No more songs." << endl;
	}
	
}




// Purpose is to remove songs from artists. It takes m as a parameter
// which is the number of views. This will remove songs that have less
// than 'm' views
int Artist::removeSong(int m)
{
	int removed = 0;

	SongNode* prevPtr = nullptr;
	SongNode* curPtr = head;
	while (curPtr != nullptr)	
	{
		if (m > curPtr->views)	// if song has fewer than M views, delete it
		{
			if (prevPtr == nullptr)
			{
				head = curPtr->next;
			}
			else
			{
				prevPtr->next = curPtr->next;
			}
			SongNode* delPtr = curPtr;
			free(curPtr->title);
			curPtr = curPtr->next;
			delete delPtr;
			removed++;
		}
		else
		{
			prevPtr = curPtr;
			curPtr = curPtr->next;
		}
	}

	return removed;
}



// Purpose is to unload data about the artists, including their top story, songs and description
void Artist::unLoadData(ofstream & outputFile)
{
	outputFile << name << ";" << topStory << ";" << description << ";\n";
	SongNode* curPtr = head;
	while (curPtr != nullptr)
	{
		outputFile << curPtr->title << ";" << curPtr->length << ";" << curPtr->views << ";" << curPtr->likes << ";\n";
		curPtr = curPtr->next;
	}
}

