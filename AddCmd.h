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
		 /*
		  * 1. This declares a member 'addClsFlag' that is never referenced anywhere except the constructor()
		  * 2. You've declared this enumeration `private` which means no code* external to the class can use
		  *    it. But you've exposed it via a public member, getFlagVaue() which as written cannot be used
		  *    externally with SHORT_FLAG or LONG_FLAG
		  * 3. As of C++11 with improvements in C++14, NSDMI (Non-static data member initialization) is allowed
		  *    and should be used where possible. Plus it's just way more convenient. In short, you can just
		  *    do:
		  * 
		  *    ClassFlag addClsFlag = SHORT_FLAG; 
		  *
		  *    This saves you from "forgetting" to initalize your member in a separate constructor, and makes
		  *    it handy for anyone reading your code to see the member with its default value all right together
		  *    here in the header
		  *
		  *    Further, in this example usage, using NSDMI would entirely negate the need for defining a custom
		  *    constructor entirely. 
		  *  4. In general, `enum class` should be preferred over c-style enums as they have a few added benefits.
		  */
		enum ClassFlag{SHORT_FLAG, LONG_FLAG} addClsFlag;
	public:
		AddCmd();
		
		/*
		 * Unclear if this is intended or not, but this function as written does not operate on any member of the
		 * AddCmd class. As such, you could have declared it as `static` which means its available to be called
		 * without having an actual object of type AddCmd.
		 * 
		 * class AddCmd {
		 *    static std::string getFlagValue(ClassFlag);
		 * };
		 * 
		 * // some other code
		 * AddCmd::getFlagValue(SHORT_FLAG)
		 */
		std::string getFlagValue(enum ClassFlag);
	};
}
#endif
