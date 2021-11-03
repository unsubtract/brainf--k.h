<h1 align="center">brainfuck.h</h1>
<p align="center">A C header that allow users to compile brainfuck programs
within a C compiler.</p>

---
You can insert the header into the top of your brainfuck source, 
and it will compile as if it were C!

Okay, not really because the preprocessor doesn't like brainfuck instructions.
<br>Instead, the language has been modified to a dialect of sorts as follows:
bf | bf.h
---:|:---
`+` | `·A`
`-` | `·S`
`>` | `·N`
`<` | `·P`
`[` | `·L`
`]` | `·C`
`.` | `·O`
`,` | `·I`

**NOTE:** The middle-dot character (**·**) represents whitespace, 
and it is **necessary** (the preprocessor gets sad without it).<br>
Due to reasons, all files must also be terminated with a `·E` instruction.

Technically this is still valid brainfuck, just with different symbols. 
In theory, if an interpreter let you use these custom symbols, the 
files would function both within the interpreter and within a C compiler 
(as originally intended).

---
### Converter
This repository includes `convert.c`, which turns regular brainfuck 
into the brainfuck.h dialect.<br>It can be built with `make convert`.

All input comes from `stdin` and all output goes to `stdout`.<br>
`argv[1]` may optionally contain the cell size expressed as an unsigned 
integer limit, and `argv[2]` may optionally contain the tape length in cells.
```sh
$ cat program.b | ./convert > program.c
```
---
### Usage
Have brainfuck.h ready in your source directory and 
add `#include "brainfuck.h"` to your source files 
(the converter does this automatically).

You can change the cell size with the `BRAINFUCK_CELLSIZE` macro, 
and tape length with the `BRAINFUCK_MEMSIZE` macro.<br>
Make sure these are defined before the include.

Now you can try it out in a C compiler:
```sh
$ cc program.c -o program
```
---
### Demos
This repository includes various brainfuck programs in `/demos/`.<br>
They can be used to try out the functionality of brainfuck.h 
and are automatically built by default with `make all` or `make demos`.

Details and credits for the demos can be found within thir respective files.

<h6 align="center">© 2021, unsubtract</h6>
