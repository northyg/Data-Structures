
/************************************/
// Giselle Northy
// CS260, Fall 2019.
// Project 4: This project utilizes a binary search tree (BST) to store
// websites and their info such as keyboard, rating, topic, summary and address
// File Name: bst.cpp
/************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "bst.h"

using namespace std;


// Constructor
BST::BST()
{
	root = nullptr;
	size = 0; // set size to 0
	height = 0;
}


// Destructor destroys the BST to free memory
BST::~BST()
{
	destroy(root);
	size = 0;
	height = 0;
}



// destroys nodes, resursive call from the destructor
void BST::destroy(Node *& currRoot)
{
	if (currRoot)
	{
		destroy(currRoot->left);
		destroy(currRoot->right);
		delete currRoot->data;
		delete currRoot;
	}
}



// This adds a website to the BST
void BST::addWebsite(Website * w)
{
	addWebsite(root, w);
	size++; // increase the count of the nodes
	updateHeight();
}



// Recursive function to add new Node
void BST::addWebsite(Node *& currRoot, Website * w)
{
	if (!currRoot)
	{
		currRoot = new Node(w);
	}
	else if (*w < *(currRoot->data))
	{
		addWebsite(currRoot->left, w);
	}
	else
	{
		addWebsite(currRoot->right, w);
	}
}



// This function retrieves and uses search
bool BST::retrieve(char* keyword, Website*& match_data)
{
	return search(root, keyword, match_data);
}



// This function searches for websites and compares keys for a match
bool BST::search(Node * currRoot, const char * key, Website*& match) const
{
	if (!currRoot)
	{
		return false;
	}

	int temp = strcmp(key, currRoot->data->getKeyword());
	if (temp == 0)
	{
		match = currRoot->data;
		return true;
	}
	else if (temp < 0)
	{
		return search(currRoot->left, key, match);
	}
	else
	{
		return search(currRoot->right, key, match);
	}
}



// displays all the websites in the BST
void BST::displayAll()
{
	displayInOrder(root);
}



// This function gets the height
int BST::getHeight()
{
	return height;
}



// This function displays the websites in order
void BST::displayInOrder(Node * root) const
{
	if (root)
	{
		displayInOrder(root->left);
		cout << root->data->getTopic() << " ";
		cout << root->data->getKeyword() << " ";
		cout << root->data->getWebsiteAddress() << " ";
		cout << root->data->getSummary() << " ";
		cout << root->data->getReview() << " ";
		cout << root->data->getRating() << endl;
		displayInOrder(root->right);
	}
}



// This function reoves websites by topic
int BST::removeWebsiteTopic(char* topic_name)
{
	int count = removeWebsiteTopic(root, topic_name);
	updateHeight();
	return count;
}



// This function removes websites by Topic, deletes nodes and edits count
int BST::removeWebsiteTopic(Node *& root, char* topic)
{
	int count = 0;
  if (root)
	{
		count += removeWebsiteTopic(root->right, topic);
		count += removeWebsiteTopic(root->left, topic);
		if (strcmp(topic, root->data->getTopic()) == 0)
		{
			deleteNode(root);
			size--;
			++count;
		}
	}
	return count;
}



// This function removes websites by keyword and updates the height
bool BST::removeWebsiteKeyWord(const char * key)
{
	bool found = removeWebsiteKeyWord(root, key);
	updateHeight();
	return found;
}



// This function removes websites by keyword in the BST
bool BST::removeWebsiteKeyWord(Node *& currRoot, const char * key)
{
	if (!currRoot)
	{
		return false;
  }
	int temp = strcmp(key, currRoot->data->getKeyword());
	if (temp == 0)
	{
		deleteNode(currRoot);
		size--;
		return true;
	}
	else if (temp < 0)
	{
		return removeWebsiteKeyWord(currRoot->left, key);
	}
	else
	{
		return removeWebsiteKeyWord(currRoot->right, key);
	}
}



//This function deletes nodes in the BST
void BST::deleteNode(Node *& aNode)
{
	bool needNewRoot = false;
	if(aNode == root)
	{
		needNewRoot = true;
	}

	if (!aNode->left && !aNode->right)
	{
		delete aNode->data;
		delete aNode;
		aNode = nullptr;
		if(needNewRoot)
		{
			root = nullptr;
		}
	}
	else if (!aNode->right)
	{
		Node * temp = aNode;
		aNode = aNode->left;
		delete temp->data;
		delete temp;
		temp = nullptr;
		if(needNewRoot)
		{
			root = aNode;
		}
	}
	else if (!aNode->left)
	{
		Node * temp = aNode;
		aNode = aNode->right;
		delete temp->data;
		delete temp;
		temp = nullptr;
		if(needNewRoot)
		{
			root = aNode;
		}
	}
	else
	{
		//find the inorder successor
		Node * prev = nullptr;
		Node * curr = aNode->right;
		while (curr->left)
		{
			prev = curr;
			curr = curr->left;
		}


		delete aNode->data;
		aNode->data = curr->data;
		if (!prev)
		{
			aNode->right = curr->right;
		}
		else
		{
			prev->left = curr->right;
		}
		delete curr;
	}
}



// This function upodates the height
void BST::updateHeight()
{
	height = updateHeight(root);
}



// This function updates the height of the BST and sets the left/right nodes
int BST::updateHeight(Node * currNode)
{
	if(currNode == nullptr)
	{
		return 0;
	}

	int leftH = updateHeight(currNode->left);
	int rightH = updateHeight(currNode->right);

	if(leftH > rightH)
	{
		return leftH + 1;
	}
	else
	{
		return rightH + 1;
	}
}
