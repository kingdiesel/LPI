#pragma once
#include <string>

class Lexer
{
public:
	void ParseTokenFile(const std::string& filename, class BNF& grammar);
};