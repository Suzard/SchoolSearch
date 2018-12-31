// School header file
#pragma once
#ifndef SCHOOL_H
#define SCHOOL_H
//used to add a next operator
class School {
private:
	int key;
	string name;
	string location;
	string rating;
	int secondary_key;
public:
	School() { key = 0; name = ""; location = ""; rating = ""; secondary_key = 0; };
	//in case where we just want to search by id
	School(int init_key) { key = init_key;};
	//when we initialize the School from reading the text file
	School(int init_key, string init_name, string init_location, string init_rating, int init_secondary_key) { key = init_key; name = init_name; location = init_location; rating = init_rating; secondary_key = init_secondary_key; };
	// Getters
	int returnKey() const { return key; };
	string returnName() const { return name; };
	string returnLocation() const { return location; }
	string returnRating() const { return rating; }
	int returnKey2() const { return secondary_key; }
	// Setters
	void setKey(int new_key) { key = new_key; };
	void setName(string new_name) { name = new_name; };
	void setLocation(string new_location) { location = new_location; }
	void setRating(string new_rating) { rating = new_rating; }
	void setKey2(int new_key2) { secondary_key = new_key2; }
};
#endif