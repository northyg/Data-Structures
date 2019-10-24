/*************************/
// Giselle Northy, 10/14/2019, Project1, recordlabel.cpp
// Description of what file contains (purpose): This program creates a list of artists
// that belong to a record label. Artists have songs associated with them. Users can
// add songs, remove songs and edit songs.
/*************************/



#include "recordlabel.h"
#include <cstring>
#include <iostream>

using namespace std;


// Purpose is to construct the record label ptr and set head to null
RecordLabel::RecordLabel()
{
	head = nullptr;	
}



/// Purpose is to decontruct the record label nodes
RecordLabel::~RecordLabel()
{
	ArtistNode* curNode = head;
	while(curNode != nullptr)
	{
		ArtistNode* delNode = curNode;
		curNode = curNode->next;
		delete delNode->artist;
		delete delNode;
	}
}
 


// Purpose is to add artists to the list and takes char name, top story and description 
bool RecordLabel::addArtist(char* artistName, char* topStory, char* description)
{
	// see if artist already exists
	Artist* artist;
	bool found = findArtist(artistName, artist);
	
	// if not found, we add this as a new artist
	if (!found)
	{
		Artist* newArtist = new Artist(artistName, topStory, description);
		addArtistList(newArtist);
	}

	return !found;
}



// Purpose is to add songs and takes the artists name, song title, length, views and likes
bool RecordLabel::addSong(char* artistName, char* title, double length, int views, int likes)
{
	// see if artist exists, cannot add a song if invalid artist
	Artist* artist;
	bool found = findArtist(artistName, artist);

	// if we found the artist, then add the song to their list of songs
	if (found)
	{
		found = artist->addSong(title, length, views, likes);
	}
	else
	{
		cout << "could not find artist " << artistName << endl;
	}

	return found;
}



// Purpose is to edit the song of an artist, the song title, views and likes
bool RecordLabel::editSong(char* artistName, char* songName, int views, int likes)
{
	Artist* artist;
	bool found = findArtist(artistName, artist);

	// if we found the artist, then attempt to edit their song
	if (found)
	{
		found = artist->editSong(songName, views, likes);	// function returns true if it finds and edits the song
	}

	return found;
}
  


// Purpose is to display songs of an artist by going through the list of songs
bool RecordLabel::displaySongs(char* artistName)
{
	Artist* artist;
	bool found = findArtist(artistName, artist);

	if (found)
	{
		artist->displaySongs();
	}

	return found;
}



// Purpose is to display the list of artists
void RecordLabel::displayArtists()
{
	ArtistNode* curNode = head;
	while (curNode != nullptr)
	{
		cout << curNode->artist->getName() << endl;
		curNode = curNode->next;
	}
}



// Purpose is to remove songs from an artist 
int RecordLabel::removeSongs(int views)
{
	int removedSongs = 0;
	ArtistNode* curNode = head;
	while (curNode != nullptr)
	{
		removedSongs += curNode->artist->removeSong(views);
		curNode = curNode->next;
	}
	
	return removedSongs;
}  
  

// Purpose is to  add a new artist to the linked list
void RecordLabel::addArtistList(Artist* art)
{
	ArtistNode* an = new ArtistNode;
	an->artist = art;
	an->next = head;
	head = an;
}



// Purpose is to find artists in the list and uses strcmp to see if the artist is in the list
bool RecordLabel::findArtist(char* artistName, Artist*& ptr)
{
	bool found = false;

	ArtistNode* curPtr = head;
	while ((curPtr != nullptr) && (!found))
	{
		if (strcmp(artistName, curPtr->artist->getName()) == 0)
		{
			found = true;
			ptr = curPtr->artist;
		}
		else
		{
			curPtr = curPtr->next;
		}
	}

	return found;
}



// Purpose is to unload the data from record label and output artists
void RecordLabel::unLoadData(ofstream & outputFile)
{
	ArtistNode* curPtr = head;
	while(curPtr != nullptr)
	{
		outputFile << "Artist:\n";
		curPtr->artist->unLoadData(outputFile);
		outputFile << "\n";
		curPtr = curPtr->next;
	}
}
