//************************************************************************
//	Jeremy Atkins
//	Professor Mackay
//	CS 121
//	4/30/18
//	Program name:	Project_3
//	Program file:	Project_3.cpp
//	Input Files:	None
//	Output Files:	AtkinsProj3Results.txt
//	Included Files:	Project_3.cpp
//	Purpose:		Takes in a text file input and processes it, 
//					returning the number of characters, words, and 
//					the percentage of the characters are a specific
//					character, sorting the characters by the percentage.
//************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//struct for holding information about each character
struct charInfo
{
	char character;
	int charCount;
	double charPercent;
};

void getFileName(ifstream&, ofstream&, string&);
void initializeArray(charInfo*);
void countWords(ifstream&, charInfo*, ofstream&, string);
void countChars(ifstream&, charInfo*);
void sortChars(charInfo*);
void printCount(charInfo*, ofstream&);


const int SIZE = 58;		//number of characters to process

int main()
{
	ifstream inFile;
	ofstream outFile;
	string fName;			//input file name
	charInfo characters[SIZE];		//array of charInfo structs


	getFileName(inFile, outFile, fName);
	initializeArray(characters);
	countWords(inFile, characters, outFile, fName);
	countChars(inFile, characters);
	sortChars(characters);
	printCount(characters, outFile);

	return 0;
}

/*
/	getFileName
/	Opens a specified text file
/	Input parameters:	ifstream reference, ofstream reference, string reference
/	Return type:	void
*/
void getFileName(ifstream& m_inFile, ofstream& m_outFile, string& m_fname)
{
	string outFile_name = "AtkinsProj3Results.txt";
	cout << "Enter the path of the file to be analyzed: ";
	cin >> m_fname;
	m_inFile.open(m_fname);
	while (!m_inFile)
	{
		cout << "Error opening file " << m_fname << endl;
		cout << "Enter the path of the file to be analyzed: ";
		cin >> m_fname;
		m_inFile.open(m_fname);
	}
	m_outFile.open(outFile_name);
	m_outFile << outFile_name << endl;
	cout << "Results written to " << outFile_name << endl;
}

/*
	initializeArray
	Initializes an array of charInfo structs using an offset to get the correct ascii value
	Input parameters:	empty array of charInfo structs
	Return type: void
*/
void initializeArray(charInfo* m_characters)
{
	for (int i = 0; i < SIZE; i++)
	{
		m_characters[i].character = i + 33;		//offset to start at the ascii value of '!'
		m_characters[i].charCount = 0;
		m_characters[i].charPercent = 0;
	}
}

/*
	countWords
	Counts the number of words in the input file, meaning every string separated by white space
	Input parameters:	ifstream reference, charInfo array, ofstream reference, string filename
	Return type: void
*/
void countWords(ifstream& m_inFile, charInfo* m_characters, ofstream& m_outFile, string m_fname)
{
	string input;
	int num_words = 0;
	m_inFile >> input;
	while (m_inFile)
	{
		num_words++;
		m_inFile >> input;
	}
	m_outFile << "\n\nThe number of words is: " << num_words << endl;

	m_inFile.close();
	m_inFile.open(m_fname);
}

/*
	countChars
	Counts the number of characters in the input file and calculates the percentage of characters the specific character represents
	Input parameters:	ifstream reference, charInfo array
	Return type: void
*/
void countChars(ifstream& m_inFile, charInfo* m_characters)
{
	
	char input;
	double total_chars = 0;
	m_inFile >> input;
	while (m_inFile)
	{
		total_chars++;
		input = toupper(input);

		//counts characters
		for (int i = 0; i < SIZE; i++)
		{
			if (m_characters[i].character == input)
			{
				m_characters[i].charCount++;
				break;
			}
		}
		m_inFile >> input;
	}
	//calculates percentage
	for (int i = 0; i < SIZE; i++)
		m_characters[i].charPercent = m_characters[i].charCount / total_chars * 100;

	m_inFile.close();
}

/*
	sortChars
	Uses an insertion sort to sort the charInfo array by character percent in descending order
	Input parameters:	charInfo array
	Return type: void
*/
void sortChars(charInfo* m_characters)
{
	charInfo temp;
	double key;
	int j;
	for (int i = 1; i < SIZE; i++)
	{
		key = m_characters[i].charPercent;
		temp = m_characters[i];
		j = i - 1;
		while (j >= 0 && m_characters[j].charPercent < key)
		{
			m_characters[j + 1] = m_characters[j];
			j--;
		}
		m_characters[j + 1].charPercent = key;
		m_characters[j + 1] = temp;
	}
}
/*
	printCount
	Prints out the charInfo array into the specified output file
	Input parameters:	charInfo array
	Return type: void
*/
void printCount(charInfo* m_characters, ofstream& m_outFile)
{
	m_outFile << "\n\nCharacter" << setw(10) << "Total" << setw(12) << "Percent" << endl;
	for (int i = 0; i < SIZE; i++)
		m_outFile << fixed << setprecision(2) << m_characters[i].character << setw(18) << m_characters[i].charCount << setw(10) << m_characters[i].charPercent << "%" << endl;

	m_outFile.close();
}