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
	std::string AddCmd::getFlagValue(enum AddCmd::ClassFlag clsFlag)
	{
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
