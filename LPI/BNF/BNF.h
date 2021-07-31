#pragma once
#include "BNFTree.h"
#include "BNFMatchResult.h"
#include <string>
#include <vector>

class BNF
{
public:
	bool ParseFile(const std::string& filename);
	bool ParseString(const std::string& bnf_string);
	bool Match(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result);
private:
	bool ParseStream(std::istream& stream);
	BNFTree m_tree;
};