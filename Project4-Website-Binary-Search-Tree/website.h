
/************************************/
// Giselle Northy
// CS260, Fall 2019
// Project 4: This project utilizes a binary search tree (BST) to store
// websites and their info such as keyboard, rating, topic, summary and address
// File Name: website.h
/************************************/

#ifndef WEBSITE_H
#define WEBSITE_H


class Website
{
public:
	Website();
	Website(char* topic, char* key, char* website, char* summary, char* review, int rating); // constructor
	~Website(); // destructor

	// DONT THINK NEED void editReview(char* review); // need char * because its a c string which is a char array
	// DONT THINK NEED	void editRating(int rating); // edit the rating for a website


	char* getTopic(); // gets the topic name
	const char* getKeyword();	// gets the keyword
	char* getWebsiteAddress(); // get website address
	char* getSummary(); // get summary
	char* getReview();
	int getRating(); // get the website rating

	Website& operator=(const Website& web);
	bool operator<(const Website& web);


private:
	char* topicName; // topic name
	char* keyword;	// keyword for website
	char* websiteAddress; // website address
	char* summary; // website summary
	char* review; // website review
	int rating; // website rating

};

#endif
