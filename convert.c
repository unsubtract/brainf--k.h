/* convert.c 1.0.0 - Convert brainfuck source into brainfuck.h friendly stuff
 * By unsubtract, ISC license, see README.md */
#include <stdio.h>

int main(int argc, char *argv[]) {
    // crappy way to parse cell and memory size
    if (argc > 1) printf("#define BRAINFUCK_CELLSIZE %s\n", argv[1]);
    if (argc > 2) printf("#define BRAINFUCK_MEMSIZE %s\n", argv[2]);
    puts("#include \"brainfuck.h\"");

    for (register int i = 0; i != EOF; i = getchar()) {
        if      (i == '+') fputs(" A", stdout);
        else if (i == '-') fputs(" S", stdout);
        else if (i == '>') fputs(" N", stdout);
        else if (i == '<') fputs(" P", stdout);
        else if (i == '[') fputs(" L", stdout);
        else if (i == ']') fputs(" C", stdout);
        else if (i == '.') fputs(" O", stdout);
        else if (i == ',') fputs(" I", stdout);
    }
    puts(" E");
    return 0;
}
