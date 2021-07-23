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

			std::vector<BNFMatchResult> results;
			const bool matched = grammar.Match(tokens, results);
			if (matched)
			{
				std::cout << token_line << " matched to\n";
				for (const BNFMatchResult& result : results)
				{
					std::cout << "\t" << result.m_symbol.GetSymbol() << ":" << result.m_expression_term.value << std::endl;
				}
				std::cout << std::endl;
			}
			else
			{
				std::cout << token_line << " was not matched." << std::endl;
			}
		}
		token_file.close();
	}
}
