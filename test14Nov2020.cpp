//============================================================================
// Name        : test14Nov2020.cpp
// Author      : me
// Version     : ALPHA 1
// Copyright   : Your copyright notice
// Description : CCG is a tool for creating and managing resources for devops.
//============================================================================

#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>
#include <regex>


//--------------------------------------//
//  CCG Components, Engine and Modules	//
//--------------------------------------//
#include "Modes.h"
#include "AddCmd.h"




/*
 * Classic method for writing to a given file name and file extension.
 * Tries to create that file and on success, CCG will let the user enter string
 * line data to be commited to the newly created file.
 *
 * This assumes that the file permissions allow the write which in most cases
 * is a true statement.
 * Another assumption is that you are able to execute this based on security
 * level and that level's assigned permissions.
 *
 * @param fileName the name of the file
 * @param fileExtension extension of the file to be created
 * */
bool writeToFile(std::string fileName, std::string fileExtension)
{
	//https://stackoverflow.com/questions/33979451/writing-lines-to-txt-file-c/33979582
	//^finally this answer with 3 votes seems to work
	//The below lets the user continue to write to the file


	std::string fullfname = fileName + "." + fileExtension;


	//https://www.daniweb.com/programming/software-development/threads/193208/converting-const-char-to-char
	//^idea came from here. Guy answered with the array approach and to use strcpy method from std
	char *charArr_fname = new char[fullfname.size() + 1];
	std::strcpy(charArr_fname, fullfname.c_str());


	//https://stackoverflow.com/questions/1057287/ofstream-error-in-c
	//^resolved ofstream issue where its scope fell under
	//create open fstream for new file
	// and try to open it
	std::ofstream myfile;
	myfile.open(charArr_fname);

	if(myfile.is_open())
	{
		std::string str;

		do
		{
			std::cout << "(" << fullfname << ")<<";
			std::getline(std::cin, str);
			myfile << str << std::endl;
		}
		while(str != "");

		std::cout << "You wrote to the file!" << std::endl;

		myfile.close();
	}
	else
	{
		std::cerr<<"Unable to open file";
		return false;
	}

	return false;
}

void execCreateFile()
{
	std::string fileName;
	std::string fileExtension;

	std::cout << "Name of your file: ";
	std::getline(std::cin, fileName);


	std::cout << "Name of your extension: ";
	std::getline(std::cin, fileExtension);

	writeToFile(fileName, fileExtension);
}


//Take user input and break up on the spaces or tabs
void parseInput(std::string inputLine)
{
	//add command flags
	//std::regex r("\\s");
//	regex space_regex("(\\s+)");
}


int main()
{
	//CCG Resource objects
	CCG::AddCmd addCmdObj ();		//apparently this is how you create instead of Java's "new" keyword



	std::cout << "CCG started. Enter 'exit' to exit." << std::endl;
	std::string ans;

	do
	{
		std::cout << ">";
		std::getline(std::cin, ans);

		//
		if(ans == "add -cls")
		{
			execCreateFile();
		}
	}
	while(ans != "exit");




	//close, done. End.
	return 0;
}

