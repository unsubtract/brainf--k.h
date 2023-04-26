<h1 align="center">brainfuck.h</h1>
<p align="center">A C header that allows building brainfuck programs
within a C compiler.</p>

---
As it turns out, the simplest brainfuck compiler is really just a C compiler
(though its far from good at it).

Using the power of the C Preprocessor and very simple character
substitution, any brainfuck program alongside this header can build
as if it were C. Unlike other simple conversions, this one should be portable
and not incur trivial errors such as buffer overflows, and can be configured
through macros. Despite all that, you [probably shouldn't use it](#caveats).

The following substitutions are used to convert a source file:
bf | bf.h
---:|:---
`+` | `INC·`
`-` | `DEC·`
`>` | `IPT·`
`<` | `DPT·`
`[` | `JNZ·`
`]` | `JZR·`
`.` | `PUT·`
`,` | `GET·`

The middle-dot character `·` represents whitespace.
All programs must be terminated with an extra `·JZR` instruction.

## Usage
After a file is converted, the macros described in
[Implementation Details](#implementation-details)
may be set (either with the `-D[MACRO]` compiler flag or in the file)
and finally the brainfuck.h header file is included after the macros.
Compile the converted source file as you would C to produce a binary.

This is **not** a header in the traditional sense (or in any sense), you never
include it as part of anything but a converted brainfuck source file,
and it contains entire blocks of code that don't compile to a translation unit.

---
A utility `mkbfhsrc` is included to automate the process of converting
brainfuck source files to brainfuck.h-compatible ones.

```
Usage: mkbfhsrc [OPTIONS] [FILE]

  -c [BITS]	bit width of cells, leave unset to use all bits in the type
  -e [FORMAT]	EOF format (0: return 0, -1: return -1, 1: leave unchanged)
  -m [BITS]	bits of address space for memory (eg. 15 bits = 32768 cells)
  -o [FILE]	output file
  -t [TYPE]	C type for cells (eg. uint32_t, \"unsigned char\")

This utility does not check for errnoneous arguments or syntax errors
If no input or output file is specified, stdin and stdout are used respectively
```

Various test programs are included in the `/tests` directory.
They must be built manually as I never got around to writing a build script.

## Implementation Details
Various brainfuck interpreters over the years have implemented the language
with minor variations. Various macros are provided to allow different
conventions to be used. These macros must appear before the header is included.

### `MEMBITS`
Bits of address space for memory (the cell count being `2 ^ MEMBITS`),
must be a positive integer.<br>Defaults to `15` (32,768 cells).

Memory will always wrap around when the pointer goes out of bounds
(implemented as a circular buffer). This prevents buffer overflows,
and cannot be configured.

### `CELLBITS`
Bit width of cells, may be any arbitrary positive integer
(though it must be smaller than `sizeof(CELL_T)*8`).
Leave unset to use the full size of `CELL_T`.<br>Defaults to unset.

### `CELL_T`
Type used to hold the cell. Must be equal to or larger in size than `CELLBITS`.
<br>Defaults to `uint8_t`.

### `EOF_FORMAT`
Convention to use when EOF is encountered on input. May be either:<br>
`0`: set the cell to 0<br>`-1`: Set the cell to its maximum value
(like `(unsigned)~0`)<br>`1`: leave the cell unchanged.<br>Defaults to `0`.

## Caveats
brainfuck.h serves mostly as an example of why macros are awful and
how not to use the preprocessor.

Its largely a toy that I thought of and quickly put together in my free time,
not realizing how disasterous it would eventually become. Macros used this way
make it impossible to catch bugs and are a pain to configure, requiring extra
burden to be placed on both the programmer and user.
