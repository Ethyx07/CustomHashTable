#pragma once
#include <iostream>
#include <cstring>
#include <vector>


using namespace std;

struct Pair {
	int key; //The unique key associated with the value (Phone number in our case)
	string value;  //The string value that links with the key (Person name)
	Pair* nextPair; //A reference to the next pair in our bucket

	Pair(int curKey, string curValue) : key(curKey), value(curValue), nextPair(nullptr){} //Constructor for our pairs, next pair is initialised null
};

//HashTable is designed to store a persons phone number (key) alongside their name (value). Phone number is key as its unique

class HashTable
{
	private:
		static const int hashGroups = 10;
		Pair* table[hashGroups];//Creates an array of hashGroups custom bucket heads 
		int numOfElements = 0;

	public:
		HashTable(); //Constructor for our hashtable, used to initialise our pairs
		~HashTable(); //Destructor for our hashtable, uses empty table to free all the pairs and prevent memory leak

		bool isEmpty() const; //Function that checks if hashtable is empty or contains pairs
		int hashFunction(int key); //Creates the hash value that corresponds to the key

		void insert(int key, string value); //Inserts a pair using the key and value. Overrides old values if key is already in use
		void remove(int key); //Removes value from bucket. If key is not in use, nothing is done
		int size(); //Returns the current size of the hash table, with all valid pairs
		string findValue(int key); //Searches for value based on inputted key

		vector<int> getAllKeys(); //Gets a vector of key integers
		vector<string> getAllValues(); //Gets all the values in the hash table

		void printAllKeys(); //Prints to console all the keys that are currently in use
		void printAllValues(); //Prints all values that are currently in use
		void printTable(); //Loops and prints entire table of pairs

		void emptyTable(); //Empties the entire table, clearing it out
};

