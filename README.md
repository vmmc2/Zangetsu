# Zangetsu

## What is it?
A compiler for a large subset of the C programming language that targets the x86-64 architecture for Linux systems, written in C++ 20.

## Why does this exist?
* One of my dreams is to work as a Compiler Engineer.
* In order to do so, well... one must know how a compiler works.
* It was important to me to write a compiler for a language that I'd actually use in real life. I didn't want to spend time with some toy programming language even though I know they have their value.
* I wanted my compiler to generate assembly code that I could run without an emulator or virtual machine
* I have previously designed a programming language called Bleach and implemented a Tree-Walk Interpreter for it. However, I felt like I was cheating in the sense that I was abstracting what is, in my opinion, the most interesting part of a compiler: How a compiler actually translate the code that we, humans, understand, to code that the machine understands (also known as machine code)? How are optimizations applied to the translated code? What are other types of IR, not considering ASTs, that are closer to the hardware?
* __According to the author of the book I used as the main reference to write Zangetsu, the C programming language is a simple language, and I agree with her, but is not a toy language. Thus, it hits a sweet spot.__
* __Moreover, the C language is a perfect example of a language that has been shaped by the systems it runs on and the people that use it. Keep in mind that some aspects of C vary between the hardware you are running it and also the operating systems. Last, but not least, some aspects of the language are left unspecified to give more freedom to the one that is implementing the compiler.__

## References:
### Books
* __Compilers: Principles, Techiniques and Tools:__ by . Also known as the "Dragon Book". It is considered the "Compilers bible". A good book for reference. It is heavily theoretical and spends most of its content on the front-end stage of a compiler.

### Papers
* __An Incremental Approach to Compiler Construction:__ by Abdulaziz Ghuloum. It explains how to write a compiler for the Scheme language targeting the x86 architecture. As the name suggests, it explains the process in an incremental way. The author starts with the simplest possible program and then adds one new language construct at a time.
