/*************************/
// Giselle Northy, 10/14/2019, Project1, artist.h
// Description of what file contains (purpose): This program creates a list of artists
// that belong to a record label. Artists have songs associated with them. Users can
// add songs, remove songs and edit songs.
/*************************/

#ifndef _ARTIST_
#define _ARTIST_

#include <fstream>
#include <stdio.h>
#include "song.h"

using namespace std;

class Artist
{
public:
	Artist(char* n, char* ts, char* desc); // Artist contructor
	~Artist(); // deconstructor 

	char* getName(); // char* to get artist name
	bool addSong(char* title, double length, int views, int likes); // add a song to artist
	bool editSong(char* song, int v, int l); // edit a song's views and likes
	void displaySongs();	// display songs for an artist
	void unLoadData(ofstream & outputFile); // unload the data to the txt file

	int removeSong(int m); // removes a song, m is the argument for views


private:

	char* name; // artists name
	SongNode* head; // ptr to the artists songs
	char* topStory; // top stories for the artist
	char* description; // info about when artist joined and genre

	void insertSong(SongNode *& current, SongNode* newSong); // recursive function to insert song into correct spot
	void displaySong(SongNode* song); // recursive call to display songs for an artist
};

#endif

