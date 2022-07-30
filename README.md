# LPI
Lexer Parser Interpreter intended for use in creating adventure games

![BuildAndTest](https://github.com/kingdiesel/LPI/actions/workflows/BuildAndTest.yml/badge.svg)

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

Matches the tokens in input line to the grammar and returns match results:
```
LOOK matched to
        <unary_verb>:LOOK

WALK NORTH matched to
        <verb>:WALK
        <noun_direction>:NORTH

GIVE EMPTY WATERFLASK TO THIRSTY GOAT matched to
        <verb>:GIVE
        <adjective>:EMPTY
        <noun_object>:WATERFLASK
        <preposition>:TO
        <adjective>:THIRSTY
        <noun_animal>:GOAT

INVALID was not matched.
```

Match results mapped to actions:
```
LookAction - examines objects
PickupAction - places objects in inventory
UseAction - uses objects (use tissue) or on other objects (use key on door)
WalkAction - scene transitions
```

Scene with SceneObjects to describe adventure game rooms with components to define object behavior:
```
SceneObject* some_object = new SceneObject();
some_object->SetID("1");
some_object->AddDescriptionComponent();
some_object->GetDescriptionComponent()->SetDescription("A regular looking llama.\n");
some_object->AddNoun("LLAMA");
       
DescriptionComponent - allows object to be the target of a LookAction
UseComponent - allows object to be the target of a UseAction
SceneExitComponent - allows object to be the target of a WalkAction
InventoryItemComponent - allows object to be the target of a PickupAction
```

Implemented sample game
```

```

