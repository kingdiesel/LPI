#include "pch.h"
#include "BNF/BNFSymbol.h"
#include "BNF/BNFSymbol.cpp"
#include <gtest/gtest.h>

namespace TestBNFSymbolStrings
{
	const std::string test_symbol("<symbol>");
	const std::string test_symbol_alternate("<lobmys>");
}
TEST(TestBNFSymbol, TestConstructor)
{
	using namespace TestBNFSymbolStrings;
	BNFSymbol symbol(test_symbol);
	EXPECT_TRUE(symbol.GetSymbol() == test_symbol);

	symbol.SetSymbol(test_symbol_alternate);
	EXPECT_TRUE(symbol.GetSymbol() == test_symbol_alternate);
	symbol.SetSymbol(test_symbol);

	BNFSymbol symbol_equals(test_symbol);
	BNFSymbol symbol_not_equals(test_symbol_alternate);
	EXPECT_TRUE(symbol == test_symbol);
	EXPECT_TRUE(symbol == symbol_equals);
	EXPECT_TRUE(symbol != test_symbol_alternate);
	EXPECT_TRUE(symbol != symbol_not_equals);
}

TEST(TestBNFSymbol, TestSetSymbol)
{
	using namespace TestBNFSymbolStrings;
	BNFSymbol symbol(test_symbol);

	symbol.SetSymbol(test_symbol_alternate);
	EXPECT_TRUE(symbol.GetSymbol() == test_symbol_alternate);
	symbol.SetSymbol(test_symbol);
}

TEST(TestBNFSymbol, TestOperatorEquals)
{
	using namespace TestBNFSymbolStrings;
	BNFSymbol symbol(test_symbol);
	BNFSymbol symbol_equals(test_symbol);
	EXPECT_TRUE(symbol == test_symbol);
	EXPECT_TRUE(symbol == symbol_equals);
}

TEST(TestBNFSymbol, TestOperatorNotEquals)
{
	using namespace TestBNFSymbolStrings;
	BNFSymbol symbol(test_symbol);
	BNFSymbol symbol_not_equals(test_symbol_alternate);
	EXPECT_TRUE(symbol != test_symbol_alternate);
	EXPECT_TRUE(symbol != symbol_not_equals);
}