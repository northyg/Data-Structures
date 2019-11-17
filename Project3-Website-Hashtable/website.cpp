
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 3: This project holds is a Hash table ADT that holds information on websites
// and is implemented using a Hash Table ADT and array data structure
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
Website::Website(char* topic, char* website, char* summ, char* rev, int rat)
{
	topicName = strdup(topic);
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
void Website::editReview(char* rev)
{
	free(review);
	review = strdup(rev);
}



// Purpose is to edit a rating for a website
void Website::editRating(int rat)
{
	rating = rat;
}



// Purpose is to get the topic of a website
char* Website::getTopic()
{
	return topicName;
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
	websiteAddress = strdup(web.websiteAddress);
	summary = strdup(web.summary);
	review = strdup(web.review);
	rating = web.rating;
	return *this;
}
