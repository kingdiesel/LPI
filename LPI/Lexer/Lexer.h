#pragma once
#include <string>
#include <vector>
struct BNFMatchResult;

class Lexer
{
public:
	void ParseTokenFile(const std::string& filename, class BNF& grammar);
	bool MatchString(const std::string& match_string, std::vector<BNFMatchResult>& results, class BNF& grammar);
	bool MatchTokens(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& results, class BNF& grammar);
};