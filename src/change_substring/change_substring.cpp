// change_substring.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <malloc.h>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

void Replace(const string &inputFileName, const string &outputFileName, const string &stringForChange, const string &stringToChange)
{
	SetConsoleOutputCP(1251);
	ifstream inputFile;
	inputFile.open(inputFileName, ifstream::in);

	if (!inputFile.good())
	{
		cout << "Error: cannot open input file!" << endl;
		exit(1);
	}

	ofstream outputFile;
	outputFile.open(outputFileName, ofstream::out);

	if (!outputFile.good())
	{
		cout << "Error: cannot create output file!" << endl;
		exit(2);
	}

	string processingString, resultString;
	while (!inputFile.eof())
	{
		getline(inputFile, processingString);

		int overlapCounter = 0;
		for (unsigned int i = 0; i < processingString.size(); ++i)
		{
			if (processingString[i] != stringForChange[overlapCounter])
			{
				overlapCounter = 0;
				resultString.push_back(processingString[i]);
			}
			else
			{
				++overlapCounter;
				resultString.push_back(processingString[i]);
				if (overlapCounter == stringForChange.size())
				{
					resultString.erase(resultString.end() - stringForChange.size(), resultString.end());
					resultString.insert(resultString.size(), stringToChange);
					overlapCounter = 0;
				}
			}
		}

		cout << resultString << endl;
		processingString.clear();
		outputFile << resultString;
		if (!inputFile.eof())
		{
			outputFile << endl;
		}
	}
}

int main(int argc, char *argv[])
{	
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	string sublineForChange = argv[3];
	string sublineToChange = argv[4];
	
	/*string inputFileName = "file3.txt";
	string outputFileName = "file3out.txt";
	string sublineForChange = "мыла";
	string sublineToChange = "красила";*/
	Replace(inputFileName, outputFileName, sublineForChange, sublineToChange);
	return 0;
}

