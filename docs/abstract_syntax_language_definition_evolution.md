# Abstract Syntax Description Language (ASDL) Evolution

## What is it?
* This file is responsible for showing the evolution of the implemented ASDL (also known as Abstract Syntax Description Language) for the subset of the C language that is being implemented by Zangetsu.
* An ASDL is a blueprint for the types that must be used when building the AST of the programming language being implemented by a compiler during the parsing stage.
* __The ASDL file is responsible for providing a formal specification of all nodes that are present inside the AST (Abstract Syntax Tree) that the parser is supposed to generate during the parsing stage of the compilation process. This file is responsible for defining the structure and the types of all AST nodes in a concise and high-level manner.__
* According to Gemini 2.5 Pro, the CPython compiler uses ASDL to define its AST.

## Explanation
* Suppose that inside the ASDL specification, I have the following line:
```
statement = Return(exp)
```
* __The line above means the following:__
  * __There exists an abstract type called ```statement```.__
  * __```Return``` is A TYPE of ```statement```.__
* Similarly, we have another example regarding ASDL specification:
```
expr = Constant(int)
```
* __The line above means the following:__
  * __There exists an abstract type called ```expr``` (which is a short for ```expresion```).__
  * __```Constant``` is A TYPE of ```expr``` (```expression```).__

## Versions
### Version ```0.1.0```
```
program = Program(function_definition)
function_definition = Function(identifier name, statement body)
statement = Return(exp)
expr = Constant(int)
```