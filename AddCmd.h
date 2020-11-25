/*
 * AddCmd.h
 *
 *  Created on: Nov 20, 2020
 *      Author: tmitchu2
 */
#ifndef ADDCMD_H
#define ADDCMD_H

namespace CCG
{
	class AddCmd
	{
	private:
		enum ClassFlag{SHORT_FLAG, LONG_FLAG} addClsFlag;
	public:
		AddCmd();
		std::string getFlagValue(enum ClassFlag);
	};
}
#endif
