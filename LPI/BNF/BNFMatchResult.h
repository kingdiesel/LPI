#pragma once
#include "BNFSymbol.h"
#include "BNFExpression.h"

struct BNFMatchResult
{
	BNFMatchResult(const BNFSymbol& symbol, const BNFExpressionTerm& term):
		m_symbol(symbol), m_expression_term(term)
	{}

	BNFSymbol m_symbol;
	BNFExpressionTerm m_expression_term;
};