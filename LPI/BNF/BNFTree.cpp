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
				BNFNode* new_node = new BNFNode(expression_term.value, std::vector<std::string>());
				node.AddChild(new_node);
				for (BNFNode& matching_node : m_nodes)
				{
					if (matching_node.GetSymbol() == expression_term.value)
					{
						new_node->AddChild(&matching_node);
					}
				}
			}
		}
	}
}

bool BNFTree::Match(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result)
{
	return m_tree_root->Match(tokens, out_result);
}

void BNFTree::GetTokenDescriptors(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result)
{
	for (const std::string& token_string : tokens)
	{
		for (const BNFNode& node : m_nodes)
		{
			if (node.GetExpression().GetNumTerms() == 1)
			{
				if (node.GetExpression().GetExpressionTerms()[0].value == token_string)
				{
					out_result.emplace_back(BNFMatchResult(node.GetSymbol(), node.GetExpression().GetExpressionTerms()[0]));
				}
			}
		}
	}
}
