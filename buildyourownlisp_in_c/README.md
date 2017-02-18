## Build Your Own Lisp (with C) Online Book

Purpose: Learn C by building a "custom" lisp that the author made. 

The author explicity states that some wouldn't even consider it a lisp because it doesn't have X. Whatever, sounds fun.


### Chapter 2: Installing

1. Type in the hello world code
2. Compile with: `cc -std=c99 -Wall hello_world.c -o hello_world`

Learn to use `gdb` to debug your programs early. It's the right way to debug.

#### gdb (or) Gnu's GDB Debugger

On a mac you get `lldb` which is similar.

- [Tutorial](http://web.archive.org/web/20161210093903/http://dirac.org/linux/gdb/) by Peter Jay Salzman


#### `valgrind` is another debugging tool

For "memory leaks or more nasty errors".


#### Online Reference for standard library

- [C reference](http://en.cppreference.com/w/c)
    - Our goal is to provide programmers with a complete online reference for the C and C++ languages and standard libraries, i.e. a more convenient version of the C and C++ standards.
    - The primary objective is to have a good specification of C and C++. That is, things that are implicitly clear to an experienced programmer should be omitted, or at least separated from the main description of a function, constant or class.

