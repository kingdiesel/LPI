#pragma
#include <string>
#include "BNFTree.h"

class BNF
{
public:
	bool Parse(const std::string& filename);
private:
	BNFTree m_tree;
};