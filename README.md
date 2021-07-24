# LPI
Lexer Parser Interpreter intended for use in creating adventure games

![Build](https://github.com/kingdiesel/LPI/workflows/MSBuild/badge.svg)

Takes a grammar file in standard [BNF format](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form):
```
; basic adventure game grammar, <command> must always be present, it's the expected root
<command> ::= <unary_verb> | <verb> <noun> | <verb> <adjective> <noun> | <verb> <adjective> <noun> <preposition> <adjective> <noun>
<unary_verb> ::= LOOK | HELP
<verb> ::= PICKUP | INSERT | GIVE | WALK | ASK
<adjective> ::= BLUE | RUSTY | THIRSTY | EMPTY | OLD
<preposition> ::= INTO | TO | ABOUT
<noun> ::= <noun_direction> | <noun_animal> | <noun_object>
<noun_direction> ::= NORTH | SOUTH | EAST | WEST
<noun_animal> ::= FROG | LLAMA | GOAT
<noun_object> ::= KEY | LOCK | WATERFLASK
```

Takes input strings:
```
LOOK
WALK NORTH
ASK LLAMA
PICKUP BLUE FROG
INSERT RUSTY KEY INTO OLD LOCK
GIVE EMPTY WATERFLASK TO THIRSTY GOAT
INVALID
```

Matches the tokens in each line to the grammar and returns match results:
```
LOOK matched to
        <unary_verb>:LOOK

WALK NORTH matched to
        <verb>:WALK
        <noun_direction>:NORTH

ASK LLAMA matched to
        <verb>:ASK
        <noun_animal>:LLAMA

PICKUP BLUE FROG matched to
        <verb>:PICKUP
        <adjective>:BLUE
        <noun_animal>:FROG

INSERT RUSTY KEY INTO OLD LOCK matched to
        <verb>:INSERT
        <adjective>:RUSTY
        <noun_object>:KEY
        <preposition>:INTO
        <adjective>:OLD
        <noun_object>:LOCK

GIVE EMPTY WATERFLASK TO THIRSTY GOAT matched to
        <verb>:GIVE
        <adjective>:EMPTY
        <noun_object>:WATERFLASK
        <preposition>:TO
        <adjective>:THIRSTY
        <noun_animal>:GOAT

INVALID was not matched.
```
