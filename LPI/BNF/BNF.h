#pragma once
#include "BNFMatchResult.h"
#include <string>
#include <vector>

class BNF
{
public:
	BNF();
	~BNF();
	bool ParseFile(const std::string& filename);
	bool ParseString(const std::string& bnf_string);
	bool Match(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result);
	void GetTokenDescriptors(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result);
private:
	bool ParseStream(std::istream& stream);
	class BNFTree* m_tree = nullptr;
};