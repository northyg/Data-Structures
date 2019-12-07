
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 4: This project utilizes a binary search tree (BST) to store
// websites and their info such as keyboard, rating, topic, summary and address
// File Name: bst.h
/************************************/



#ifndef BST_H
#define BST_H

#include "website.h"


// BST uses nodes to store information on websites
class BST
{
public:

	BST(); // constructor
	~BST(); // destructor
	void addWebsite(Website * w); // insert
	int removeWebsiteTopic(char* topic_name); // remove all websites to a topic name
	bool removeWebsiteKeyWord(const char* keyword); // remove one website based on a keyword
	bool retrieve(char* keyword, Website*& match_data); // NOTE You do not need to call retrieve to remove
	void displayAll(); // displays all the websites in the table alphabetically by key word
	int getHeight(); // gets the height of the tree



// Struct node has pointers to websites and their data
private:
	struct Node
	{
		Node(Website* aWebsite)
		{
			data = aWebsite;
			left = right = nullptr;
		}
		Website* data; // data is ptr that points to a website
		Node* left; // left node
		Node* right; // right node
	};

	Node * root; // top node
	int size; // number of nodes
	int height; // height of the tree

	// private functions
	void destroy(Node *& currHead); // destroys nodes, resursive call from the destructor
	void addWebsite(Node *& currRoot, Website * w); // add a website
	bool search(Node * currRoot, const char * key, Website*& match) const; // search the websites
	void displayInOrder(Node * currRoot) const; // display websites in order
	int removeWebsiteTopic(Node *& root, char* topic); // remove a website topic
	bool removeWebsiteKeyWord(Node *& currRoot, const char * key); // remove a website by keyword
	void deleteNode(Node *& aNode); // delete a node
	void updateHeight(); // update the height of tree
	int updateHeight(Node * currNode); // update the height of tree
};
#endif
