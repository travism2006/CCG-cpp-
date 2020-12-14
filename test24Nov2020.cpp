//============================================================================
// Name        : test24Nov2020.cpp
// Author      : TMM
// Version     :
// Copyright   : I own all copyrights as of 24 November 2020.
//
//							CCG Application
//						-----------------------
//			Taking automation, scripting, and abstraction into your
//			development.  Using CCG you can create ANT builds, test cases for web apps and more.
//			Considering security, CCG is a standalone system that will be isolated from the Internet.
//			Templates are a big factor in CCG for creating and managing projects of all sizes.
//			As a whole, CCG is meant to be a tool.  Many developers could use it on the same network and there would be no crossover or integrity issues, or leaks from CCG.
//============================================================================

#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>
#include <regex>

// Time to include my modules for CCG down here:
#include "AddCmd.h"
#include "Modes.cpp"
#include "Lexer.h"

/**
 * Collect user input that will write to a specified file. May or may not echo
 * back the users line data.
 * */
void execWriteStringLineData(const std::string &fullFileName, std::string lineStrData, std::ofstream &myFile, bool echoLines)
{
	do
	{
		std::cout << "(" << fullFileName << ")<<";

		std::getline(std::cin, lineStrData);

		myFile << lineStrData << std::endl;

		if (echoLines)
		{
			std::cout << lineStrData << std::endl;
		}
	} while (lineStrData != "");
}

// Assumes that success and echo modes are turned off.
// When echo is on, requires the original command string.
void writeStrLineData(const std::string &originalCmmdStr, const std::string &fullFileName, std::string lineStrData, std::ofstream &myFile, bool successMode = false, bool echoMode = false, int echoModeSpecificity = CCG::Engine::echoModeWholeOperation)
{
	// https://stackoverflow.com/questions/33979451/writing-lines-to-txt-file-c/33979582
	// ^finally this answer with 3 votes seems to work
	// The below lets the user continue to write to the file

	std::cout << "Hit enter 2 times when done writing data to your file." << std::endl ;

	if (echoMode)
	{
		//Line by line or whole operation can be applied with echo mode turned on, so a total of 3 cases
		if(echoModeSpecificity == (CCG::Engine::echoModeLineSpecific + CCG::Engine::echoModeWholeOperation))
		{
			std::cout << "echo on: " << originalCmmdStr;
			execWriteStringLineData(fullFileName, lineStrData, myFile, true);
		}
		else if(echoModeSpecificity == CCG::Engine::echoModeLineSpecific)
		{
			execWriteStringLineData(fullFileName, lineStrData, myFile, true);
		}
		else if(echoModeSpecificity == CCG::Engine::echoModeWholeOperation)
		{
			std::cout << "echo on: " << originalCmmdStr;
			execWriteStringLineData(fullFileName, lineStrData, myFile, false);
		}

		if(successMode)
		{std::cout << "You wrote to the file!" << std::endl;}
	}

	//else if echo is turned off:
	execWriteStringLineData(fullFileName, lineStrData, myFile, false);

	if(successMode)
	{std::cout << "You wrote to the file!" << std::endl;}
}

/*
 * Tries to create that file and on success, CCG will let the user enter string
 * line data to be committed to the newly created file.
 *
 * This assumes that the file permissions allow the write which in most cases
 * is a true statement.
 * Another assumption is that you are able to execute this based on security
 * level and that level's assigned permissions.
 *
 * @param fullFileName the name of the file with its file extension
 * */
bool writeToFile(const std::string &fullFileName, const std::string &originalCmmdStr)
{
	// https://www.daniweb.com/programming/software-development/threads/193208/converting-const-char-to-char
	// ^idea came from here. Guy answered with the array approach and to use strcpy method from std
	char *charArr_FullFileName = new char[fullFileName.size() + 1];
	std::strcpy(charArr_FullFileName, fullFileName.c_str());


	// https://stackoverflow.com/questions/1057287/ofstream-error-in-c
	// ^resolved ofstream issue where its scope fell under
	std::ofstream myFile;
	myFile.open(charArr_FullFileName);

	if(myFile.is_open())
	{
		std::string lineStrData;

		writeStrLineData(originalCmmdStr, fullFileName, lineStrData, myFile, false);
		myFile.close();
	}
	else
	{
		std::cerr << "Unable to open file";
		return false;
	}
	return true;
}

void promptsToCreateFile(const std::string &originalCmmdStr)
{
	std::string fileName;
	std::string fileExtension;

	std::cout << "File Name: ";
	std::getline(std::cin, fileName);


	std::cout << "File Extension (without the dot character): ";
	std::getline(std::cin, fileExtension);

	const std::string fullFileName = fileName + "." + fileExtension;


	if (writeToFile(fullFileName, originalCmmdStr) /* && CCG::onOperationSuccess */ )
	{
		std::cout << "Successful write to file" << std::endl;
	}
}

// Take user input and break up on the spaces or tabs




int main(void)
{
	//CCG Resource objects
	CCG::AddCmd addCmdObj ();		//apparently this is how you create instead of Java's "new" keyword
	CCG::Lexer ccgLexer;

	std::cout << "CCG started. Enter 'exit' to exit." << std::endl;
	std::string ans;

	do
	{
		std::cout << ">";
		std::getline(std::cin, ans);

		//parse and show
		ccgLexer.inputLexer(ans);

		if(ans == "add -cls")
		{
			promptsToCreateFile(ans);
		}

	}
	while(ans != "exit");

	//close, done. End.
	return 0;
}
