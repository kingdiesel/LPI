#include "BNFSymbol.h"

BNFSymbol::BNFSymbol(const std::string& symbol)
{
}

bool BNFSymbol::operator==(const BNFSymbol& rhs)
{
	return m_symbol == rhs.m_symbol;
}

const std::string& BNFSymbol::GetSymbol() const
{
	return m_symbol;
}

void BNFSymbol::SetSymbol(const std::string& symbol)
{
	m_symbol = symbol;
}
