
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 4: This project utilizes a binary search tree (BST) to store
// websites and their info such as keyboard, rating, topic, summary and address
// File Name: website.cpp
/************************************/

#include <cstdlib>
#include <cstring>
#include "website.h"



// Constructor sets private data members to nullptr
Website::Website() : topicName(nullptr), websiteAddress(nullptr), summary(nullptr), review(nullptr)
{

}



// Constructor
Website::Website(char* topic, char* key, char* website, char* summ, char* rev, int rat)
{
	topicName = strdup(topic);
	keyword = strdup(key);
	websiteAddress = strdup(website);
	summary = strdup(summ);
	review = strdup(rev);
	rating = rat;
}




// Destructor frees the memory
Website::~Website()
{
	if (topicName != nullptr)
	{
		free(topicName);
	}
	if (keyword != nullptr)
	{
		free(keyword);
	}
	if (websiteAddress != nullptr)
	{
		free(websiteAddress);
	}
	if (summary != nullptr)
	{
		free(summary);
	}
	if (review != nullptr)
	{
		free(review);
	}
}



// Purpose is to edit a review for a website
	// DONT THINK NEED void Website::editReview(char* rev)
//{
	//free(review);
	//review = strdup(rev);
//}



// Purpose is to edit a rating for a website
	// DONT THINK NEEDvoid Website::editRating(int rat)
//{
	//rating = rat;
//}



// Purpose is to get the topic of a website
char* Website::getTopic()
{
	return topicName;
}



// Purpose is to get the keyword of a website
const char* Website::getKeyword()
{
	return keyword;
}



// Purpose is to get the website address of a website
char* Website::getWebsiteAddress()
{
	return websiteAddress;
}



// Purpose is to get the summary of a website
char* Website::getSummary()
{
	return summary;
}



// Purpose is to get the review of a website
char* Website::getReview()
{
	return review;
}



// Purpose is to get the rating of a website
int Website::getRating()
{
	return rating;
}



// This is an overloaded function for the assignment feature
// Which ensures all the data members get copied over
// This function is necessary!
Website& Website::operator=(const Website& web)
{
	topicName = strdup(web.topicName);
	keyword = strdup(web.keyword);
	websiteAddress = strdup(web.websiteAddress);
	summary = strdup(web.summary);
	review = strdup(web.review);
	rating = web.rating;
	return *this;
}



// This function compares keywords
bool Website::operator<(const Website& web)
{
	bool result = false;
	if (strcmp(keyword, web.keyword) < 0)
	{
		result = true;
	}
	return result;
}
