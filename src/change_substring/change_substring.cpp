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

	string processingString;
	while (!inputFile.eof())
	{
		getline(inputFile, processingString);

		size_t i = 0;
		while (i < (processingString.size() - stringForChange.size() + 1))
		{
			bool canChangeSubstring = true;
			if (processingString[i] == stringForChange[0])
			{
				for (unsigned int j = 1; j < stringForChange.size(); ++j)
				{
					if (processingString[i + j] != stringForChange[j])
					{
						canChangeSubstring = false;
						break;
					}
				}
				if (canChangeSubstring)
				{
					outputFile << stringToChange;
					i += stringForChange.size();
				}
				else
				{
					outputFile << processingString[i];
					++i;
				}
			}
			else
			{
				outputFile << processingString[i];
				++i;
			}
		}
		while (i < processingString.size())
		{
			outputFile << processingString[i];
			++i;
		}
		processingString.clear();
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
	
	Replace(inputFileName, outputFileName, sublineForChange, sublineToChange);
	return 0;
}

