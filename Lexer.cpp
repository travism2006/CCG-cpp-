/*
 * Lexer.cpp
 *
 *  Created on: Dec 6, 2020
 *      Author: tmitchu2
 */

#include "Lexer.h"
#include <regex>
#include <iostream>

namespace CCG
{
	void Lexer::inputLexer(std::string inputLine)
	{
		// concept from informit.com/articles/article.aspx?p=2064649&seqNum=7
		const std::regex re("[\\s+]");
		std::sregex_token_iterator iterLexer(inputLine.begin(), inputLine.end(), re, -1);
		std::sregex_token_iterator regexEnd;

		for(; iterLexer != regexEnd; ++iterLexer)
		{
			std::cout << iterLexer->str() << std::endl;
		}
	}
}
