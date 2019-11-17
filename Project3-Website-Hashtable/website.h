
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 3: This project holds is a Hash table ADT that holds information on websites
// and is implemented using a Hash Table ADT and array data structure
// File Name: website.h
/************************************/

#ifndef WEBSITE_H
#define WEBSITE_H


class Website
{
public:
	Website();
	Website(char* topic, char* website, char* summary, char* review, int rating); // constructor
	~Website(); // destructor

	void editReview(char* review); // need char * because its a c string which is a char array
	void editRating(int rating); // edit the rating for a website


	char* getTopic(); // gets the topic name
	char* getWebsiteAddress(); // get website address
	char* getSummary(); // get summary
	char* getReview(); 
	int getRating(); // get the website rating
	
	Website& operator=(const Website& web);
	

private:
	char* topicName; // topic name
	char* websiteAddress; // website address
	char* summary; // website summary
	char* review; // website review
	int rating; // website rating
	
};

#endif
