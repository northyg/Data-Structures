/*************************/
// Giselle Northy, 10/14/2019, Project1, recordlabel.h
// Description of what file contains (purpose): This program creates a list of artists
// that belong to a record label. Artists have songs associated with them. Users can
// add songs, remove songs and edit songs.
/*************************/


#ifndef _RECORD_LABEL_
#define _RECORD_LABEL_

#include <fstream>
#include <stdlib.h>
#include "artist.h"

using namespace std;

class RecordLabel
{
public:
	RecordLabel(); // record label contructor
	~RecordLabel(); // record label destructor
  
	bool addArtist(char* artistName, char* topStory, char* description); // addArtist
	bool addSong(char* artistName, char* title, double length, int views, int likes); //addSong
	bool editSong(char* artistName, char* songName, int views, int likes); // edits songs
  
	bool displaySongs(char* artistName); // displays songs for an artist
	void displayArtists(); // displays artists
	int removeSongs(int views); // removes songs
 	void unLoadData(ofstream & outputFile); // unloads the data  
  

private:
	struct ArtistNode // struct artist creates nodes
	{
		Artist* artist;
		ArtistNode* next;
	};
  
	ArtistNode* head;

	void addArtistList(Artist* art); // makes a list for artists
	bool findArtist(char* artistName, Artist *& ptr); // find artists

};



#endif //_RECORD_LABEL_
