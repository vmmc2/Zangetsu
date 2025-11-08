# Lexical Grammar Evolution

## What is it?
* This file is responsible for showing the evolution of the implemented lexical grammar for the subset of the C language that is being implemented by Zangetsu.

## Versions
### Version ```0.1.0```
```
|       Token       | Regular Expression |
|-------------------|--------------------|
| Identifier        | [a-zA-Z_]\w*\b     |
| Constant          | [0-9]+\b           |
| ```int``` keyword     | int\b              |
| "void" keyword    | void\b             |
| "return" keyword  | return\b           |
| Left Parenthesis  | \(                 |
| Right Parenthesis | \)                 |
| Left Brace        | {                  |
| Right Brace       | }                  |
| Semicolon         | ;                  |
```