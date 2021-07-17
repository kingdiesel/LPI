#pragma once
#include <string>

class Lexer
{
public:
	bool InitializeGrammar(const std::string& filename);
	void ParseTokenFile(const std::string& filename, class BNF& grammar);
};