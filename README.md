# Zangetsu

## What is it?
A compiler for a large subset of the C programming language (specifically C17) that targets the x86-64 architecture for Linux systems, written in C++ 20.

## Why does this exist?
* One of my dreams is to work as a Compiler Engineer.
* In order to do so, well... one must know how a compiler works.
* It was important to me to write a compiler for a language that I'd actually use in real life. I didn't want to spend time with some toy programming language even though I know they have their value.
* I wanted my compiler to generate assembly code that I could run without an emulator or virtual machine
* I have previously designed a programming language called Bleach and implemented a Tree-Walk Interpreter for it. However, I felt like I was cheating in the sense that I was abstracting what is, in my opinion, the most interesting part of a compiler: How a compiler actually translate the code that we, humans, understand, to code that the machine understands (also known as machine code)? How are optimizations applied to the translated code? What are other types of IR, not considering ASTs, that are closer to the hardware?
* __According to the author of the book I used as the main reference to write Zangetsu, the C programming language is a simple language, and I agree with her, but is not a toy language. Thus, it hits a sweet spot.__
* __Moreover, the C language is a perfect example of a language that has been shaped by the systems it runs on and the people that use it. Keep in mind that some aspects of C vary between the hardware you are running it and also the operating systems. Last, but not least, some aspects of the language are left unspecified to give more freedom to the one that is implementing the compiler.__

## Nice To Have (Optional) Features
* Such features are considered to be hard by the author. Thus, one should carefully consider if this is worth all the trouble. Below, I have listed some of such features:
  - [ ] Binary, octal and hexadecimal integer constants.
  - [ ] Usage of ```typedef```.
  - [ ] Pointer to functions.

## Meaning of Certain Files
* __```CMakePresets.json```:__ This file defines which build configurations are officially supported by your project (in this case, Zangetsu). For example: "Debug Build with GCC on Linux", "Release Build with Clang", etc.
* __```CMakeUserPresets.json```:__ This is a personal file. You should put your own version of it within the root directory of this project/repository. It is basically responsible for storing personal local preferences. For example, it is within this file that you put the path to ```vcpkg.cmake``` (where you tell CMake where to find your dependences). __It is also worth mentioning that the ```CMakeUserPresets.json``` file inherits from the ```CMakePresets.json``` file.__ 

## References:
### Books
* __Compilers: Principles, Techiniques and Tools:__ by Alfred V. Aho, Monica S. Lam, Ravi Sethi and Jeffrey D. Ullman. Also known as the "Dragon Book". It is considered the "Compilers bible". A good book for reference. It is heavily theoretical and spends most of its content on the front-end stage of a compiler.
* __Intel 64 Software Developer’s Manual:__ Intel’s official documentation for the x64 instruction set (which can be found [here](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)). There are 2 volumes available. However, we care about Volume 2, the instruction set reference. There’s also an unofficial version [here](https://www.felixcloutier.com/x86/).

### Websites
* __Compiler Explorer:__  A website where you can see how a variety of widely used compilers translate your code to assembly.

### Papers
* __An Incremental Approach to Compiler Construction:__ by Abdulaziz Ghuloum. It explains how to write a compiler for the Scheme language targeting the x86 architecture. As the name suggests, it explains the process in an incremental way. The author starts with the simplest possible program and then adds one new language construct at a time.

### Specifications
* __C Standard Specification:__ Responsible for specifying how C programs are supposed to behave. For Zangetsu, we'll C17 (ISO/IEC 9899:2018), which was the latest version of the standard at the time the major reference book for this project was being written. There is a free draft version that can be accessed [here](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf), which is an early draft of C23.
* __System V Application Binary Interface (ABI) Specification:__  This defines a set of conventions that executables follow on Unix-like operating systems, which is the case for Linux. This will be important starting in Chapter 9, when we implement function calls. The latest version of this spec can be found [here](https://gitlab.com/x86-psABIs/x86-64-ABI).
