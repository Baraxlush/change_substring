// change_substring.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <malloc.h>
#include <string>
#include <fstream>

using namespace std;

FILE* Open_File_To_Read(char *name_file)
{
	FILE *file_inp = fopen(name_file, "r");
	if (file_inp == NULL)
	{
		printf("Error: cannot load input file!\n");
		system("pause");
		exit(1);
	}
	return file_inp;
}

FILE* Open_File_To_Write(char *name_file)
{
	FILE *file_out = fopen(name_file, "w");
	if (file_out == NULL)
	{
		printf("Error: cannot create output file!\n");
		system("pause");
		exit(1);
	}
	return file_out;
}

void Change_strings(FILE* input, FILE* output, string string_for_change, string string_to_change)
{
	string processed_line;
	processed_line.reserve(200);
	int overlap_counter = 0;
	
	while (!feof(input))
	{
		char line_for_subsidiary_implementation[500];
		fgets(line_for_subsidiary_implementation, 500, input);
		processed_line = line_for_subsidiary_implementation;
		for (unsigned int i = 0; i < processed_line.size(); i++)
		{
			if (processed_line[i] != string_for_change[overlap_counter])
				overlap_counter = 0;

			else
			{
				overlap_counter++;
				if (overlap_counter == string_for_change.size())
				{
					processed_line.erase(i + 1 - string_for_change.size(), string_for_change.size());
					processed_line.insert(i + 1 - string_for_change.size(), string_to_change);
					overlap_counter = 0;
					i = i - string_for_change.size() + string_to_change.size();
				}
			}
		}
		fprintf(output, "%s", processed_line.c_str());
	}
	fclose(input);
	fclose(output);
}

int main(int argc, char *argv[])
{
	char *file_name_inpup = argv[1];
	FILE *file_inp = Open_File_To_Read(file_name_inpup);

	char *file_name_output = argv[2];
	FILE *file_out = Open_File_To_Write(file_name_output);

	string subline_for_change = argv[3];
	string subline_to_change = argv[4];
	
	Change_strings(file_inp, file_out, subline_for_change, subline_to_change);
	return 0;
}

