#include "Lexer.h"
#include "BNF/BNF.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>

void Lexer::ParseTokenFile(const std::string& filename, BNF& grammar)
{
	std::ifstream token_file;
	token_file.open(filename);
	if (token_file.is_open())
	{
		std::string token_line;
		while (token_file.good())
		{
			std::getline(token_file, token_line);
			
			// split by spaces
			std::regex regex_split_spaces("\\s");
			std::vector<std::string> tokens
			(
				std::sregex_token_iterator(token_line.begin(), token_line.end(), regex_split_spaces, -1),
				std::sregex_token_iterator()
			);

			std::vector<BNFMatchResult> result;
			const bool matched = grammar.Match(tokens, result);
		}
		token_file.close();
	}
}
