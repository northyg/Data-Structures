/*************************/
// Giselle Northy, 10/14/2019, Project1, song.h
// Description of what file contains (purpose): This program creates a list of artists
// that belong to a record label. Artists have songs associated with them. Users can
// add songs, remove songs and edit songs.
/*************************/

#ifndef _SONG_
#define _SONG_

struct SongNode // makes song nodes
{
	char* title; // song title
	double length; // song length in minutes
	int views; // song views
	int likes; // song number of likes
	
	SongNode* next; // song node ptr
	
};

#endif

