#pragma once
#include <string>
#include <vector>
struct BNFMatchResult;

class Lexer
{
public:
	// parses a token file, mainly used for testing
	void ParseTokenFile(const std::string& filename, class BNF& grammar);

	// given a grammar, will provide maching on a single string, the string will be
	// split by spaces before processing into "tokens"
	bool MatchString(const std::string& match_string, std::vector<BNFMatchResult>& results, class BNF& grammar);

	// same as MatchString except it expects a tokenized input
	bool MatchTokens(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& results, class BNF& grammar);

	// given a grammar, will return token descriptors on the matching tokens.
	// the tokens may not be a valid combination for the grammar, so this is to get
	// meta data about the tokens
	void GetTokenDescriptorsFromString(const std::string& match_string, std::vector<BNFMatchResult>& results, class BNF& grammar);
};