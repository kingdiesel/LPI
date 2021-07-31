#pragma once
#include "BNFNode.h"
#include "BNFMatchResult.h"
#include <vector>

class BNFTree
{
public:
	void AddNode(const BNFNode& node);
	void Populate();
	bool Match(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result);

private:
	std::vector<BNFNode> m_nodes;
	BNFNode* m_tree_root = nullptr;
};