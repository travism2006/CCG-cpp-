/*
 * AddCmd.cpp
 *
 *  Created on: Nov 20, 2020
 *      Author: tmitchu2
 */
#include <string>
#include "AddCmd.h"
//using namespace std;

namespace CCG
{
	 /* 
	  * The `enum` keyword is not needed here. I've never actually seen this, althugh I suppose it compiles
	  * 
	  * Also, this function seems more like its returning the name not the value??
	  * AddCmd::getFlagName(AddCmd::ClassFlag clsFlag);
	  * 
	  * Yes, a bit of a stretch/nit-pick but names really do matter when programs get larger and more complex
	  */
	std::string AddCmd::getFlagValue(enum AddCmd::ClassFlag clsFlag)
	{
	   /*
		 * You technically don't need the scope AddCmd:: here since you are inside a member function of this class
		 */
		if(clsFlag == AddCmd::SHORT_FLAG)
			{return "-cls";}
		else if(clsFlag == AddCmd::LONG_FLAG)
			{return "--class";}
		return "invalid";
	}

	AddCmd::AddCmd()
	{
		addClsFlag = SHORT_FLAG;
	}
}
