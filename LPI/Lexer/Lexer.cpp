#include "Lexer.h"
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
			
			// split by defined as token ::=
			std::regex regex_split_spaces("\\s");
			std::vector<std::string> split_by_spaces
			(
				std::sregex_token_iterator(token_line.begin(), token_line.end(), regex_split_spaces, -1),
				std::sregex_token_iterator()
			);
		}

		token_file.close();
	}
}
