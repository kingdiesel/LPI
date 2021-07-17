#pragma once
#include "BNFNode.h"
#include <vector>

class BNFTree
{
public:
	void AddNode(const BNFNode& node);
private:
	std::vector<BNFNode> m_nodes;
};