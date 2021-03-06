﻿#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>
#include <fstream>

using namespace std;

int main()
{
	// Prompt for user input 
	cout << "Please input the letters you have." << endl;

	string lettersIhave;
	cin >> lettersIhave;

	// Load the letters you have into a vector with the boolean
	vector<pair<char, bool>>theWord;

	for (size_t i = 0; i < lettersIhave.size(); ++i)
	{
		theWord.push_back(make_pair(lettersIhave[i], false));	// Initialized to false
	}

	// Will have to load entire dictionary for reference
	string currentWord;
	vector<string> dictionary;

	// Identify different length solutions (massively improves efficiency)
	vector<string> solution3;
	vector<string> solution4;
	vector<string> solution5;
	vector<string> solution6;

	bool found = true;
	int numCorrect = 0;

	ifstream dictionaryLoader;
	dictionaryLoader.open("dictionary.txt");

	// Ensure that the dictionary file has been opened correctly
	if (dictionaryLoader.is_open())
	{
		cout << "The dictionary file has been opened correctly, will begin loading it..." << endl;
	}
	else
	{
		cout << "The dictionary file was NOT opened correctly, exiting now.";
	}

	while (dictionaryLoader >> currentWord)
	{
		dictionary.push_back(currentWord);
	}

	// The dictionary will be loaded at this point, close the input file stream
	dictionaryLoader.close();

	// Index each word in the dictionary
	for (size_t i = 0; i < dictionary.size(); ++i)
	{
		// All words less than three characters long can be ignored. The dictionary is not perfect and this version of scrabble does not allow 1/2 character words
		if (dictionary[i].size() >= 3 && dictionary[i].size() <= 6)
		{
			// Index through each character in each word
			for (size_t x = 0; x < dictionary[i].size(); ++x)
			{
				// Index through each character that is provided
				for (size_t y = 0; y < theWord.size(); ++y)
				{
					// If the character is in here AND its "used" is FALSE
					if (dictionary[i][x] == theWord[y].first && theWord[y].second == false)
					{
						theWord[y].second = true;	// It is essential to mark each character as used
						++numCorrect;	// This integer will be used to determine if the word can be made with the letters available
						break;
					}
				}

			}

			// Sort the possible words by size, longer words are more important (worth more points)
			if (numCorrect == dictionary[i].size())
			{
				if (dictionary[i].size() == 3)
				{
					solution3.push_back(dictionary[i]);
				}
				else if (dictionary[i].size() == 4)
				{
					solution4.push_back(dictionary[i]);
				}
				else if (dictionary[i].size() == 5)
				{
					solution5.push_back(dictionary[i]);
				}
				else if (dictionary[i].size() == 6)
				{
					solution6.push_back(dictionary[i]);
				}
			}

			// Reset the usage boolean for each letter that is available
			for (size_t i = 0; i < theWord.size(); ++i)
			{
				theWord[i].second = false;
			}

			// Reset the numCorrect variable for the next word
			numCorrect = 0;
		}
	}

	// Output all the words found, the longest words go last so they are easily found
	cout << endl << "THE THREE CHARACTER WORDS: " << endl;
	while (!solution3.empty())
	{
		cout << solution3.back() << endl;
		solution3.pop_back();
	}

	cout << endl << "THE FOUR CHARACTER WORDS: " << endl;
	while (!solution4.empty())
	{
		cout << solution4.back() << endl;
		solution4.pop_back();
	}

	cout << endl << "THE FIVE CHARACTER WORDS: " << endl;
	while (!solution5.empty())
	{
		cout << solution5.back() << endl;
		solution5.pop_back();
	}

	cout << endl << "THE SIX CHARACTER WORDS: " << endl;
	while (!solution6.empty())
	{
		cout << solution6.back() << endl;
		solution6.pop_back();
	}

	cout << endl;

	return 0;
}
