#include "BNFSymbol.h"

BNFSymbol::BNFSymbol(const std::string& symbol):
m_symbol(symbol)
{
}

bool BNFSymbol::operator==(const BNFSymbol& rhs) const
{
	return m_symbol == rhs.m_symbol;
}

bool BNFSymbol::operator==(const std::string& rhs) const
{
	return m_symbol == rhs;
}

bool BNFSymbol::operator!=(const BNFSymbol& rhs) const
{
	return !(*this == rhs);
}

bool BNFSymbol::operator!=(const std::string& rhs) const
{
	return !(*this == rhs);
}

const std::string& BNFSymbol::GetSymbol() const
{
	return m_symbol;
}

void BNFSymbol::SetSymbol(const std::string& symbol)
{
	m_symbol = symbol;
}
