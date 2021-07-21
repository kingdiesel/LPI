#pragma
#include "BNFTree.h"
#include "BNFMatchResult.h"
#include <string>
#include <vector>

class BNF
{
public:
	bool Parse(const std::string& filename);
	bool Match(std::vector<std::string> tokens, std::vector<BNFMatchResult>& out_result);
private:
	BNFTree m_tree;
};