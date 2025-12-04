#include "HashTable.h"

HashTable::HashTable() {
	for (int i = 0; i < hashGroups; i++) { //Sets all table values as nullptr to prevent the table array containing garbage values/addresses
		table[i] = nullptr;
	}
}

HashTable::~HashTable() {
	emptyTable(); //Deletes all pairs within the buckets and clears the table entirely
}

int HashTable::hashFunction(int key) {
	return abs(key) % hashGroups; //Returns the remainder of the key, this remainder is used as the index for the bucket. Added abs in case of user error with -tive keys
}

bool HashTable::isEmpty() const{	
	for (int i = 0; i < hashGroups; i++) { //Loops through all buckets and checks if any of them are not null
		if (table[i] != nullptr) { //Not null means it contains at least 1 Pair reference
			return false;
		}
	}
	return true;
}

string HashTable::findValue(int key) {
	int hashValue = hashFunction(key);
	Pair* currentPair = table[hashValue]; //Gets pair at the start of the bucket

	while (currentPair != nullptr) { //Loops until reaches the end of the linked list
		if (currentPair->key = key) {
			return currentPair->value;
		}
		currentPair = currentPair->nextPair;
	}
	
	return "[WARNING] Key is not valid or currently in use";
}


void HashTable::insert(int key, string value) {
	int hashValue = hashFunction(key);
	
	Pair* currentPair = table[hashValue]; //Gets the first pair in that bucket. Each is linked by the nextPair reference after this

	while (currentPair != nullptr) { //Loops through linked list one by one, if it reaches a currentPair that is null, then the key isnt in the list and needs to be added
		if (currentPair->key == key) { //If key matches and it is already in the bucket, value is replaced
			currentPair->value = value;
			cout << "[WARNING] Value has been replaced as key is in use" << endl;
			return;
		}
		currentPair = currentPair->nextPair; //If key doesnt match, it takes the currentPair's next Pair and sets that as the new one.
	}

	Pair* newPair = new Pair(key, value); //Creates a new pair to be added at the start of the bucket
	newPair->nextPair = table[hashValue]; //Sets the current first pair reference as the nextPair for this pair
	table[hashValue] = newPair; //The table[hashValue] only stores the first pair in its linked list, with each pair storing the next after that
	numOfElements++; //Only increments when a new pair is added as size isnt changed when a value is updated
	cout << "Pair has been successfully added" << endl;
}

void HashTable::remove(int key) {
	int hashValue = hashFunction(key);
	Pair* currentPair = table[hashValue]; //Gets the starting/header pair of the bucket
	Pair* previousPair = nullptr; //Stores the previous pair (starts nullptr as it is set when currentPair is updated
	
	while (currentPair != nullptr) {
		if (currentPair->key == key) {
			if (previousPair == nullptr) { //Have to check previous as if its not null we would be removing everything to the left of this list
				table[hashValue] = currentPair->nextPair; //Pushes the current pair out of the table
			}
			else {
				previousPair->nextPair = currentPair->nextPair; //previousPair->nextPair is the same reference as currentPair so it replaces it with the nextPair thus removing it
			}
			delete currentPair; //Deletes current pair. Since its reference in the list is already been replaced can now be deleted
			numOfElements--; //Removes element only if the key is valid
			cout << "Pair removed" << endl;
			return;	
		}
		currentPair = currentPair->nextPair;
	}
	cout << "Key not currently in use" << endl;
	return;
}

int HashTable::size() {
	return numOfElements; //Number of elements changes when one is inserted and removed. Uses this instead of looping keeps size function as O(1) instead of O(n)
}

vector<int> HashTable::getAllKeys() {
	vector<int> keys;
	for (int i = 0; i < hashGroups; i++) { //Loops through entire hash and stores all the keys in use
		Pair* currentPair = table[i];
		while (currentPair != nullptr) {
			keys.push_back(currentPair->key);
			currentPair = currentPair->nextPair;
		}
	}
	return keys;
}

void HashTable::printAllKeys() {
	vector<int> keys = getAllKeys();

	for (int i = 0; i < keys.size(); i++) { //Loops through vector array of keys and prints each int
		cout << "Keys: " << keys[i] << endl;
	}
}

vector<string> HashTable::getAllValues() {
	vector<string> values;
	for (int i = 0; i < hashGroups; i++) { //Loops through collection of hashGroups and all pairs in the bucket, stores values in values vector
		Pair* currentPair = table[i];
		while (currentPair != nullptr) {
			values.push_back(currentPair->value);
			currentPair = currentPair->nextPair;
		}
	}
	return values;
}

void HashTable::printAllValues() {
	vector<string> values = getAllValues(); //Uses gets function so users can just call this function instead of passing in the values

	for (int i = 0; i < values.size(); i++) { //Loops through vector array of values and prints
		cout << "Values: " << values[i] << endl;
	}
}

void HashTable::emptyTable() {
	
	for (int i = 0; i < hashGroups; i++) { //Loops through every bucket and deletes the pairs
		Pair* currentPair = table[i];
		while (currentPair != nullptr) {
			Pair* tempPair = currentPair; //Stores reference as tempPair so we can change currentPair to the next in the linked list and then still delete the now previous pair
			currentPair = currentPair->nextPair;
			delete tempPair;
		}
		table[i] = nullptr;
	}
	cout << "Hash table has been cleared" << endl;
}

void HashTable::printTable() {
	for (int i = 0; i < hashGroups; i++) { //Loops through each bucket and prints their key & value
		Pair* currentPair = table[i];
		while (currentPair != nullptr) { //Once currentPair is nullptr it means that the linked list has ended
			cout << "Key: " << currentPair->key << " and Value: " << currentPair->value << endl;
			currentPair = currentPair->nextPair;
		}
	}
}


int main() {
	HashTable HT;

	if (HT.isEmpty()) {
		cout << "Table is empty" << endl;
	}
	
	HT.insert(10234, "Bobby"); //Testing insert of unique keys and values
	HT.insert(902, "Sam");
	HT.insert(1290, "Betty");
	HT.insert(2304, "Charles");
	HT.insert(9908, "Anna");
	HT.insert(12, "Richard");
	cout << "[Initial Test Table]" << endl;
	HT.printTable(); //Tests and prints table

	HT.insert(902, "Bondi"); //Testing the logic when a key already being used is replaced
	HT.insert(9, "Anna"); //Demonstrating how names/values can be the same as others
	cout << HT.size() << endl;
	cout << "[Testing Double Up Table]" << endl;
	HT.printTable();

	cout << "Please remove an item {Type key}" << endl; //Testing the removal function with user input
	int keyToRemove;
	cin >> keyToRemove;
	HT.remove(keyToRemove);
	cout << "[Testing Remove Table]" << endl;
	HT.printTable();
	cout << HT.size() << endl;
	cout << "Please enter an invalid key {Type key}" << endl; //Testing the remove functionality when a key is invalid
	cin >> keyToRemove;
	HT.remove(keyToRemove);

	cout << "Please enter a key for a value you are searching for {Type key}" << endl; //Gets key user is searching for
	int keyToSearch;
	cin >> keyToSearch;
	cout << "You searched for " << HT.findValue(keyToSearch) << endl; //Returns value that corresponds to the key searched

	cout << "Now please enter a key that doesn't exist in the table {Type key}" << endl;
	cin >> keyToSearch;
	cout << HT.findValue(keyToSearch) << endl;
	


	return 0;
}