#pragma once
class BNFSymbol;
class LPIUtil
{
public:
	static bool IsVerb(const BNFSymbol& symbol);
	static bool IsNoun(const BNFSymbol& symbol);
	static bool IsAdjective(const BNFSymbol& symbol);
	static bool IsPreposition(const BNFSymbol& symbol);
};