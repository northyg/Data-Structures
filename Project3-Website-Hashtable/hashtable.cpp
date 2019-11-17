
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 3: This project holds is a Hash table ADT that holds information on websites
// and is implemented using a Hash Table ADT and array data structure
// File Name: hashtable.cpp
/************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "hashtable.h"

using namespace std;


// Constructor
HashTable::HashTable()
{
	size = 0; // set size to 0
	currCapacity = INIT_CAP;
	hashTable = new Node*[currCapacity];
	for(int i = 0; i < currCapacity; i++)
	{
		hashTable[i] = nullptr;
	}
}


// Destructor destroys the hashtable to free memory
HashTable::~HashTable()
{
	for(int i = 0; i < currCapacity; i++)
	{
		destroy(hashTable[i]);
	}
	delete[] hashTable;
	size = 0;
}


// This adds a website to the hash table
void HashTable::addWebsite(Website * w)
{
	size++; // increase the count of the nodes
	int index = hashFunction(w->getTopic());
	
	Node* newNode = new Node(w);
	newNode->next = hashTable[index];
	hashTable[index] = newNode;
}



// Purpose is to remove all websites with a 1 star rating
int HashTable::removeWebsite()
{
	int numRemoved = 0; // # of websites removed
	for(int i = 0; i < currCapacity; i++)
	{
		numRemoved += removeLowRating(hashTable[i]);  // if null ptr, reached the end of the chain
	}
	return numRemoved;
}




// find all websites that have the getTopic() to be the same as topic_keyword
// save all of those results into all_matches array, so long as the size remains 
// smaller than array_size. If more matches found than array size, only the first
// array_size results will be put into all_matches. 
// Returns number of results put into all_matches. Zero if none found
int HashTable::retrieve(char* topic_keyword, Website all_matches[], int array_size)
{
	int foundMatches = 0;
	
	int i = hashFunction(topic_keyword);
	
	Node* current = hashTable[i];
	while(current != nullptr)
	{
		if(strcmp(topic_keyword,current->data->getTopic()) == 0) // pass 2 char ptrs, if contents are = it returns 0
		{	
			// we found a website with the desired topic
			if (foundMatches < array_size)
			{
				all_matches[foundMatches] = *current->data;
				foundMatches++;
			}
		}
		
		current = current->next;
	}
	
	
	return foundMatches;
}



// modify the review and rating for a topic and website match
bool HashTable::editWebsite(char* topic_keyword, char* website, char* new_review, int new_rating)
{
	bool foundWebsite = false;
	int i = hashFunction(topic_keyword);
	Node* current = hashTable[i];
	
	while(current != nullptr)
	{
		if ((strcmp(topic_keyword,current->data->getTopic()) == 0) &&
		    (strcmp(website,current->data->getWebsiteAddress()) == 0))
		{
			current->data->editReview(new_review);
			current->data->editRating(new_rating);
			foundWebsite = true;
		}
		
		current = current->next; // check the next node
	}
	
	return foundWebsite;
}



// takes in keyword to search for
// if there is a topic, all of those will be in the same linked list
// that means we dont have to go through the entire hash table, just the topic
void HashTable::display(char* topic_keyword)
{
	int i = hashFunction(topic_keyword);
	Node* current = hashTable[i];
	
	while(current != nullptr)
	{
		if(strcmp(topic_keyword,current->data->getTopic()) == 0) // pass 2 char ptrs, if contents are = it returns 0
		{	
			cout << current->data->getTopic() << " ";
			cout << current->data->getWebsiteAddress() << " ";
			cout << current->data->getSummary() << " ";
			cout << current->data->getReview() << " ";
			cout << current->data->getRating() << endl;
		}
		current = current->next; // check the next node
	}	
}


// displays all the websites in the table
void HashTable::displayAll()
{
	for(int i = 0; i < currCapacity; i++)
	{
		Node* current = hashTable[i];
		while(current != nullptr)
		{
			cout << current->data->getTopic() << " ";
			cout << current->data->getWebsiteAddress() << " ";
			cout << current->data->getSummary() << " ";
			cout << current->data->getReview() << " ";
			cout << current->data->getRating() << endl;
			current = current->next;
		}
	}
}



// destroys nodes, resursive call from the destructor
void HashTable::destroy(Node *& currHead)
{
	if(currHead != nullptr)
	{
		destroy(currHead->next);
		delete currHead->data;
		delete currHead;
	}
}



// converts the topic into the index integer for the table
int HashTable::hashFunction(const char* key) const
{
	int total = 0;

	int i = 0;
	while (*key)
	{
		total += *key * (i+1);
		key++;
		i++;
	}

	return total % currCapacity;
}


// Resursive function to remove low rating website
int HashTable::removeLowRating(Node* & current)
{
	int numRemoved = 0;
	if (current != nullptr)
	{
		numRemoved = removeLowRating(current->next); // recursively call on next node
		
		if(current->data->getRating() == 1) // remove all websites with a 1 star rating
		{
			++numRemoved;
			Node* temp = current;
			current = current->next;
			delete temp->data;
			delete temp;
		}
	}
	return numRemoved;
}
