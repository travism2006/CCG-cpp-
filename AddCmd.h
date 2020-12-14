/*
 * AddCmd.h
 *
 * Created on: 24 November, 2020
 * Author: tmitchu2
 */


#ifndef ADDCMD_H
#define ADDCMD_H

namespace CCG
{
	class AddCmd
	{
	private://
	public:
//		AddCmd();
		const std::string shortClassFlag = "-cls";
		const std::string longClassFlag = "--class";

		bool execute();
	};
}
#endif

