# Syntax Grammar Evolution

## What is it?
* This file is responsible for showing the evolution of the implemented syntax grammar (also known as context-free grammar) for the subset of the C language that is being implemented by Zangetsu.

## Versions
### Version ```0.1.0```
```
<program> ::= <function>
<function> ::= "int" IDENTIFIER "(" "void" ")" "{" <statement> "}"
<statement> ::= "return" <exp> ";"
<exp> ::= INTEGER
```
