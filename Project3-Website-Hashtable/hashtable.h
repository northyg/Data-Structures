
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 3: This project holds is a Hash table ADT that holds information on websites
// and is implemented using a Hash Table ADT and array data structure
// File Name: hashtable.h
/************************************/



#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "website.h"


// Hash table uses an array to store information on websites
class HashTable
{
public:

	HashTable(); // constructor
	~HashTable(); // destructor
	void addWebsite(Website * w);
	int removeWebsite(); // remove all websites with a 1 star rating
	int retrieve(char* topic_keyword, Website* all_matches, int array_size);
	bool editWebsite(char* topic_keyword, char* website, char* new_review, int new_rating); // modify the review and rating for a topic and website match
	void display(char* topic_keyword); // takes in keyword to search for
	void displayAll(); // displays all the websites in the table


private:
	struct Node
	{
		Node(Website* aWebsite)
		{
			data = aWebsite;
			next = nullptr;
		}
		Website* data; // data is ptr that points to a website
		Node* next;
	};

// private data members
Node ** hashTable;
const int INIT_CAP = 2; // Picked 2 because requirements are pick a Prime number. Reminder: Need to see how many collisions this causes. 
// Then change INIT_CAP to a different prime number (3, 5, 7, 11, 13, 17, etc.) and see how many collisions
int size; // number of nodes
int currCapacity; //current size of the number of indexes for the table

// private functions
void destroy(Node *& currHead); // destroys nodes, resursive call from the destructor
int hashFunction(const char* key) const; // converts the topic into the index integer for the table
int removeLowRating(Node* & current); // Resursive function to remove low rating website


};
#endif
