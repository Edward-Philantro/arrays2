/////////////////////////////////////////////////////////////////////
// Name: Eduardo gutierrez
// Date: 11/13/2025
// Class: CSCI 1470.04
// Semester: Fall 2025
// CSCI 1470 Instructor: Dr. Jonatan Reyes
// Program Description: Enter here your description of what the program does
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include<iomanip>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

const int MAX_WORDS = 466551;
const string LINEAR_SEARCH_UNSORTED = "LINEAR_UNSORTED";
const string LINEAR_SEARCH_SORTED = "LINEAR_SORTED";
const string BINARY_SEARCH = "BINARY";
const int dictionary = 466551;
void initiliseElements(string arr[], int size, string words1);
void arrayPopulation(string arr[], ifstream& inputfile, int size, bool check);


bool spellCheck1(const string arr[], string& word, string LINEAR_SEARCH_UNSORTED);
bool spellCheck2(const string arr[], string& word, string LINEAR_SEARCH_SORTED);
bool spellCheck3(const string arr[], string& word, string BINARY_SEARCH);
const bool debug = false;

int main() {
	string elements;
	ifstream inputfile, settingfile;
	inputfile.open("dictionary.txt");

	string* arr_dict = new string[dictionary];
	int MAX_MIS_ALLOWED = 0;
	string CHOSEN_SEARCH;
	bool check = true;
	char contin = 'n';
	int counter = 0;
	string searchType;


	settingfile.open("settings_3.txt");
	if (!settingfile) {
		cerr << "Failed to open settings file" << endl;
		return 1;
	}

	settingfile >> MAX_MIS_ALLOWED;
	settingfile >> searchType;

	initiliseElements(arr_dict, dictionary, elements);
	arrayPopulation(arr_dict, inputfile, dictionary, check);

	if (searchType == LINEAR_SEARCH_SORTED || searchType == BINARY_SEARCH) {
		sort(arr_dict, arr_dict + dictionary);
	}

	cout << "*******************************" << endl;
	cout << "Hello! Welcome to spell checker" << endl;
	cout << "*******************************" << endl << endl;

	if (debug == true) {
		do {

			cout << "Please enter a word: ";
			string word;
			cin >> word;
			cout << endl;
			bool found = false;
			if (searchType == LINEAR_SEARCH_UNSORTED) {
				auto start1 = high_resolution_clock::now();
				found = spellCheck1(arr_dict, word, searchType);
				auto end1 = high_resolution_clock::now();
				duration<double> elapsed1 = end1 - start1;

				cout << setprecision(2) << fixed << showpoint;
				if (found) {
					cout << "The Word " << word << " is spelled correctly, Amazing!" << endl;
					cout << "Linear Search took " << elapsed1.count() << " microseconds." << endl << endl;
					cout << "Do you want to continue (Y/N): ";
					cin >> contin;
					counter = 0;
					cout << endl;
				}
				else {
					cout << "oops, " << word << " isnt right.. give it another shot." << endl;
					contin = 'y';
					counter++;
				}

			}
			else if (searchType == LINEAR_SEARCH_SORTED) {
				auto start1 = high_resolution_clock::now();
				found = spellCheck2(arr_dict, word, searchType);
				auto end1 = high_resolution_clock::now();
				duration<double> elapsed1 = end1 - start1;

				cout << setprecision(2) << fixed << showpoint;
				if (found) {
					cout << "The Word " << word << " is spelled correctly, Amazing!" << endl;
					cout << "Linear Search took " << elapsed1.count() << " microseconds." << endl << endl;
					cout << "Do you want to continue (Y/N): ";
					cin >> contin;
					counter = 0;
					cout << endl;
				}
				else {
					cout << "oops, " << word << " isnt right.. give it another shot." << endl;
					contin = 'y';
					counter++;
				}

			}
			else if (searchType == BINARY_SEARCH) {
				auto start1 = high_resolution_clock::now();
				found = spellCheck3(arr_dict, word, searchType);
				auto end1 = high_resolution_clock::now();
				duration<double> elapsed1 = end1 - start1;

				cout << setprecision(2) << fixed << showpoint;
				if (found) {
					cout << "The Word " << word << " is spelled correctly, Amazing!" << endl;
					cout << "Binary Search took " << elapsed1.count() << " microseconds." << endl << endl;
					cout << "Do you want to continue (Y/N): ";
					cin >> contin;
					counter = 0;
					cout << endl;
				}
				else {
					cout << "oops, " << word << " isnt right.. give it another shot." << endl;
					contin = 'y';
					counter++;
				}
			}

		} while (contin != 'n' && counter < MAX_MIS_ALLOWED);
		if (counter == MAX_MIS_ALLOWED) {
			cout << "You have reached the maximum number (" << counter << ") of misspelled words allowed." << endl;
		}
		else
			cout << endl << "Thanks for using!!!\n\n";


		settingfile.close();
		inputfile.close();
	}
	else {
		do {

			cout << "Please enter a word: ";
			string word;
			cin >> word;

			bool found = false;
			if (searchType == LINEAR_SEARCH_UNSORTED) {
				found = spellCheck1(arr_dict, word, searchType);
			}
			else if (searchType == LINEAR_SEARCH_SORTED) {
				found = spellCheck2(arr_dict, word, searchType);
			}
			else if (searchType == BINARY_SEARCH) {
				found = spellCheck3(arr_dict, word, searchType);
			}

			if (found) {
				cout << "The Word " << word << " is spelled correctly, Amazing!" << endl << endl;
				cout << "Do you want to continue (Y/N): ";
				cin >> contin;
				counter = 0;
				cout << endl;
			}
			else {
				cout << "oops, " << word << " isnt right.. give it another shot." << endl;
				contin = 'y';
				counter++;
			}




		} while (contin != 'n' && counter < MAX_MIS_ALLOWED);
		if (counter == MAX_MIS_ALLOWED) {
			cout << endl << "You have reached the maximum number (" << counter << ") of misspelled words allowed." << endl;
		}
		else
			cout << "Thanks for using!!!\n\n";


		settingfile.close();
		inputfile.close();
	}
	return 0;
}

bool spellCheck1(const string arr[], string& word, string LINEAR_SEARCH_UNSORTED) {
	int i = 0;
	bool found = false;
	while ((i < dictionary) && (!found)) {
		if (arr[i] == word) {
			found = true;
		}
		else {
			i++;
		}


	}

	return found;
}
bool spellCheck2(const string arr[], string& word, string LINEAR_SEARCH_SORTED) {
	int i = 0;
	bool found = false;
	while ((i < dictionary) && (!found)) {
		if (arr[i] == word) {
			found = true;
		}
		else if (arr[i] > word) {
			i = dictionary;
		}
		else {
			i++;
		}


	}

	return found;
}
bool spellCheck3(const string arr[], string& word, string BINARY_SEARCH) {
	int first = 0;
	int last = dictionary - 1;
	int middle;
	bool found = false;
	while (first <= last && !found) {
		middle = (first + last) / 2;
		if (word == arr[middle]) {
			found = true;
		}
		else if (word < arr[middle]) {
			last = middle - 1;
		}
		else {
			first = middle + 1;
		}
	}

	return found;
}

void initiliseElements(string arr[], int size, string words1) {
	words1 = "";
	for (int i = 0; i < size; i++) {
		arr[i] = words1;
	}
}

void arrayPopulation(string arr[], ifstream& inputfile, int size, bool check) {

	if (!inputfile) {
		cout << "file not opened correctly T_T";
		check = false;
	}
	else {
		check = true;
	}
	string words2;
	int index = 0;
	while (index < size && inputfile >> words2) {
		arr[index] = words2;
		index++;
	}

}


