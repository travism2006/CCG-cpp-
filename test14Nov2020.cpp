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
/*
 * 1. You're passing both input parameters "by-value", which implicitly makes copies of the strings 
 *    before passing them to the writeToFile() method
 * 
 *    since writeToFile() does not need to modify either input string, there's no reason to make copies*
 * 
 *    Instead, you should "pass-by-reference", where instead of making a copy to pass, you pass a reference
 *    (or pointer) to the object instead.
 *
 *    Syntax is as follows:
 *    bool writeToFile(const std::string& fileName, const std::string& fileExtension)
 * 
 *    If you're not familiar with the `const` keyword, now is a good time to read about it and 
 *    "const correct" coding philoshopy. It may seem like unnecessary typing at first, but its good habbit
 *    to reinforce now as it improves readability, expresses intent, and allows the compiler to aid in 
 *    protecting you from yourself and others
 * 
 * 2. Accepting a fileName and fileExtension as separate parameters is a small violation of the "single 
 *    responsibility" principle for good programming practices. This function's purpose and responsibility 
 *    is writing to a file. Generating a full filename from name and extension is additional an unnecessary
 *    responsibility best moved elsewhere. This is a very minor detail, arguably so minor as to not even
 *    be worth mentioning, but its good to think about what a function does (and says it does) and keep
 *    it focused on one and only one thing. As with all "rules", "conventions", "practices", there are time
 *    when follwing them to the "t" is a fools erand, but people smarter than you with more experience
 *    have come up with them and teach them for a reason.
*/
bool writeToFile(std::string fileName, std::string fileExtension)
{
	//https://stackoverflow.com/questions/33979451/writing-lines-to-txt-file-c/33979582
	//^finally this answer with 3 votes seems to work
	//The below lets the user continue to write to the file

   /* If you were following "const correctness" fully, fullfname would be `const` as its not modified after 
	 * initializations. Some consider making local variables const an "extreme" interpretation on "const 
	 * correctness", but just pointing it out. I will not call out const unless aggregious going forward */
	std::string fullfname = fileName + "." + fileExtension;


	/*
	 * This is one way to make a copy of character string, but a few issues:
	 *   1. There's no reason to make a copy; you do the work to make a copy just to pass it off to another
	 *      method unchanged
	 *   2. strcpy() is considered "unsafe" as it can lead to buffer overruns and stack overflows. You shold
	 *      instead use one of the newer "safe" versions such as strncpy() which specifies the length of the
	 *      destination buffer
	 *   3. You should have gotten warnings about strcpy() being unsafe. 
	 *      - Take the time now to ensure you have your compiler warnings set high enough that this emits a 
	 *        warning
	 *      - Also take the time now to change your compiler settings to enable "warnings treated as errors"
	 *      - You should *always* have warnings enabled and you should not ignore them. You'll thank yourself
	 *      - in the future when you don't spend hours debugging an issue that was caught by a warning. Do it
	 *      - now.
	 */
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

		/*
		 * You should technically check the output file's ::badbit to check if there was an error during the 
		 * write, before making such proclomatinos 
		 * 
		 * if (!myfile)
		 *    std::cout << "Error writing to file\n";
		 */
		std::cout << "You wrote to the file!" << std::endl;

		myfile.close();
		
		/*
		 * This will return false even on success
	    */
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
/* 
 * likey should be pass-by-reference again, (const std::string& inputLine)
 */
void parseInput(std::string inputLine)
{
	//add command flags
	//std::regex r("\\s");
//	regex space_regex("(\\s+)");
}


int main()
{
	//CCG Resource objects
   /*
	 * C++ supports new, although it is somewhat less used with modern c++ ala C++11/C++14. 
	 * I'm not suggesting `new` should be used here (it shouldn't), just that it exists
	 * 
	 * The whole topic for initialization on c++ is complicated and there are over a dozen ways to
	 * initialize an object. For now, I'd just use whatever makes the most sense for you.
	 * 
	 * CCG::AddCmd addCmdObj;
	 * CCG::AddCmd addCmdObj();
	 * CCG::AddCmd addCmdObj = {};
	 */
	CCG::AddCmd addCmdObj ();		//apparently this is how you create instead of Java's "new" keyword


   /*
	 * std::endl forces the output stream to "flush", which can incur a performance penalty if your 
	 * writting a good deal of data to the stream. As a general rule of thumb, std::endl should be
	 * reserved for when you actually want to flush the stream buffer, and '\n' should be preferred
	 * if you simply want a carrage return to start a new line
	 */
	std::cout << "CCG started. Enter 'exit' to exit." << std::endl;
	
	/*
	 * No reason for this variable's scope to be outside the do-while loop
	 */
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
	
	/*
	 * You possibly wrote to a file unnsuccesfully (you even returned a bool), you should not return
	 * and exit code of zero (SUCCESS) if your program did not indeed succeed.
	return 0;
}

