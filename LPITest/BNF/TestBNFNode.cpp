#include "pch.h"
#include "BNF/BNFNode.cpp"
#include <gtest/gtest.h>
namespace TestBNFNodeStrings
{
	const std::string test_symbol("<symbol>");
	const std::vector<std::string> two_expressions{ "SOME_VERB", "SOME_OTHER_VERB" };
	const std::vector<std::string> one_token{ "SOME_VERB" };
	const std::vector<std::string> one_other_token{ "NONSENSE" };
}

TEST(TestBNFNode, TestConstructor)
{
	using namespace TestBNFNodeStrings;
	BNFNode node(test_symbol, two_expressions);
	EXPECT_TRUE(node.GetSymbol() == test_symbol);
	ASSERT_TRUE(node.GetExpression().GetExpressionTerms().size() == 1);
	EXPECT_TRUE(node.GetExpression().GetExpressionTerms()[0].value == two_expressions[0]);
	EXPECT_TRUE(node.GetExpression().GetExpressionTerms()[1].value == two_expressions[1]);
}

TEST(TestBNFNode, TestMatch)
{
	using namespace TestBNFNodeStrings;
	BNFNode node(test_symbol, two_expressions);
	std::vector<BNFMatchResult> results;
	EXPECT_TRUE(node.Match(one_token, results));
	ASSERT_TRUE(results.size() == 1);
	EXPECT_TRUE(results[0].m_symbol == test_symbol);
	EXPECT_TRUE(results[0].m_expression_term.value == one_token[0]);
}

TEST(TestBNFNode, TestNotMatch)
{
	using namespace TestBNFNodeStrings;
	BNFNode node(test_symbol, two_expressions);
	std::vector<BNFMatchResult> results;
	EXPECT_FALSE(node.Match(one_other_token, results));
	ASSERT_TRUE(results.size() == 0);
}