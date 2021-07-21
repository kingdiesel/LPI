#include "BNFTree.h"
#include <cassert>

void BNFTree::AddNode(const BNFNode& node)
{
	m_nodes.push_back(node);
}

void BNFTree::Populate()
{
	assert(m_tree_root == nullptr);
	// root node is special, it's the command command
	m_tree_root = new BNFNode("<command>", std::vector<std::string>());
	for (BNFNode& node : m_nodes)
	{
		if (node.GetSymbol() == "<command>")
		{
			m_tree_root->AddChild(&node);
		}
	}

	for (BNFNode& node : m_nodes)
	{
		for (const BNFExpressionTerm& expression_term : node.GetExpression().GetExpressionTerms())
		{
			if (expression_term.is_redirect)
			{
				for (BNFNode& matching_node : m_nodes)
				{
					if (matching_node.GetSymbol() == expression_term.term)
					{
						node.AddChild(&matching_node);
					}
				}
			}
		}
	}
}
