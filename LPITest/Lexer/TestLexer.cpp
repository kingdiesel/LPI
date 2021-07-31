#include "pch.h"
#include <gtest/gtest.h>
#include "BNF/BNF.cpp"
#include "BNF/BNFTree.cpp"

namespace TestLexerStrings
{
	const std::string grammar = "; basic adventure game grammar, <command> must always be present, it's the expected root\n"
		"<command> ::= <unary_verb> | <verb> <noun> | <verb> <adjective> <noun> | <verb> <adjective> <noun> <preposition> <adjective> <noun>\n"
		"<unary_verb> ::= LOOK | HELP\n"
		"<verb> ::= PICKUP | INSERT | GIVE | WALK | ASK\n"
		"<adjective> ::= BLUE | RUSTY | THIRSTY | EMPTY | OLD\n"
		"<preposition> ::= INTO | TO | ABOUT\n"
		"<noun> ::= <noun_direction> | <noun_animal> | <noun_object>\n"
		"<noun_direction> ::= NORTH | SOUTH | EAST | WEST\n"
		"<noun_animal> ::= FROG | LLAMA | GOAT\n"
		"<noun_object> ::= KEY | LOCK | WATERFLASK\n";
}

TEST(TestLexer, TestMatch)
{
	BNF grammar;
	const bool parsed_grammar = grammar.ParseString(TestLexerStrings::grammar);
	EXPECT_TRUE(parsed_grammar);
}