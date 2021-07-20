#pragma once
#include "BNFNode.h"
#include <vector>

class BNFTree
{
public:
	void AddNode(const BNFNode& node);
	void Populate();
private:
	std::vector<BNFNode> m_nodes;
	BNFNode* m_tree_root = nullptr;
};