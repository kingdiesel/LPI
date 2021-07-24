#include "pch.h"
#include "BNF/BNFExpression.cpp"
#include <gtest/gtest.h>
namespace TestBNFExpressionStrings
{
	const std::vector<std::string> one_expression{ "SOME_VERB" };
	const std::vector<std::string> two_expressions{ "SOME_VERB", "SOME_OTHER_VERB" };
	const std::vector<std::string> two_redirect_expressions{ "<redirect>", "<other_redirect>" };
}

TEST(TestBNFExpression, TestConstructor)
{
	using namespace TestBNFExpressionStrings;
	BNFExpression expression(one_expression);
	ASSERT_TRUE(expression.GetExpressionTerms().size() == 1);
	EXPECT_TRUE(expression.GetExpressionTerms()[0].value == one_expression[0]);
	EXPECT_TRUE(expression.GetExpressionTerms()[0].is_redirect == false);
}

TEST(TestBNFExpression, TestNumTerms)
{
	using namespace TestBNFExpressionStrings;
	BNFExpression expression_one_term(one_expression);
	EXPECT_TRUE(expression_one_term.GetNumTerms() == 1);

	BNFExpression expression_two_term(two_expressions);
	EXPECT_TRUE(expression_two_term.GetNumTerms() == 2);
}

TEST(TestBNFExpression, TestRedirect)
{
	using namespace TestBNFExpressionStrings;
	BNFExpression redirect_expression(two_redirect_expressions);
	for (const BNFExpressionTerm& term : redirect_expression.GetExpressionTerms())
	{
		EXPECT_TRUE(term.is_redirect);
	}
}