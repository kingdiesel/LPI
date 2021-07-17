#pragma once
#include <string>

class BNFSymbol
{
public:
	BNFSymbol() = default;
	~BNFSymbol() = default;

	BNFSymbol(const std::string& symbol);

	bool operator==(const BNFSymbol& rhs);

	const std::string& GetSymbol() const;
	void SetSymbol(const std::string& symbol);
private:
	std::string m_symbol;
};