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

## The functioning of ASDL
### Intro
* The hierarchy between AST nodes is defined by the ASDL file.
* What we need to do is translate the formal rules from the ASDL file to a construction with C++, which can model this formal grammar with: __Inheritance and Polymorphism.__

### Golden Rule of ASDL
* __The real distinction between being a Base (Abstract) Class or a Derived (Concrete) Class in ASDL is not just "appearing on both sides (left side and right side of a ```=```)", but rather that several options (constructors) exist on the right-hand side..__
* In Computer Science, we call this __Sum Types vs. Product Types.__

### When a class is a Base class (Abstract)?
* __When the right side represents a CHOICE between several options, there are multiple options on right side of the ```=``` operator. Even though, in Chapter 1, there is only one option, the nature of the type is to be a category.__
* Think about the rule:
```
stmt = Return(expr)
```
* __Even though there is just one option at Chapter 1, we have to agree that there exists several types of statements besides the ```return``` statement: ```if``` statements, ```for``` statements, ```while``` statements, and so on... (the list is large).__
* Another good way of thinking about it is the need for polymorphism. For example, ```ReturnNode``` needs another type to inherit from. In this case, ```StatementNode``` comes into play.

### When a class is a Derived class (Concrete)?
* __When the right side of the ```=``` operator represents a SINGLE fixed structure. There are no "options" or "variants." It's a one-to-one definition.__
* In the following case:
```
function_definition = Function(identifier name, statement body)
```
* __Is there any other type of function definition in C besides a ```Function```? No.__
* __The ```function_definition``` is exactly the same thing as the ```Function``` constructor.__
* __In short:__
  * However, since there's a one-to-one relationship (there's only one way to define a function), __we apply a design optimization called Class Collapse.__
  * We ignore the intermediate name (```function_definition```) and use only the constructor (```Function```) as the concrete class.
  * Instead of: ```Program``` has a pointer to ```FunctionDefinitionNode``` that points to ```FunctionNode```. We do: ```Program``` has a direct pointer to ```FunctionNode```.

## Versions
### Version ```0.1.0```
```
program = Program(function_definition)
function_definition = Function(identifier name, stmt body)
stmt = Return(expr)
expr = Constant(int)
```