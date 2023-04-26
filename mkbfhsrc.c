/* mkbfhsrc.c 3.0.0 - convert brainfuck sources into brainfuck.h
 * By unsubtract, MIT license, see README.md */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void convert(FILE *inf, FILE *outf,
        const char *membits, const char *cellbits,
        const char *cellt, const char *eofformat);
static void pexit(const char *s);
static void pusage(const char *binname);


int main(int argc, char *argv[])
{
    int i;
    FILE *outf = stdout, *inf = stdin;
    char expecting_param = 0, membits[4], cellbits[4], cellt[32], eofformat[3];
    *membits = '\0'; *cellbits = '\0'; *cellt = '\0'; *eofformat = '\0';

    /* warning: disasterous code */
    for (i = 1; i < argc; ++i) {
        if (expecting_param) {
            if (!strcmp(argv[i - 1], "-o")) {
                outf = fopen(argv[i], "w");
                if (outf == NULL) pexit(argv[i]);
            }
            else if (!strcmp(argv[i - 1], "-m")) snprintf(membits, 4, "%s", argv[i]);
            else if (!strcmp(argv[i - 1], "-c")) snprintf(cellbits, 4, "%s", argv[i]);
            else if (!strcmp(argv[i - 1], "-t")) snprintf(cellt, 32, "%s", argv[i]);
            else if (!strcmp(argv[i - 1], "-e")) snprintf(eofformat, 3, "%s", argv[i]);
            else pusage(argv[0]);
            expecting_param = 0;
        }

        else if (argv[i][0] == '-') {
            if (i < argc - 1) expecting_param = 1;
            else pusage(argv[0]);
        }

        else {
            inf = fopen(argv[i], "r");
            if (inf == NULL) pexit(argv[i]);
        }
    }

    convert(inf, outf, membits, cellbits, cellt, eofformat);

    fclose(inf);
    fclose(outf);
    return EXIT_SUCCESS;
}


static void convert(
    FILE *inf, FILE *outf,
    const char *membits, const char *cellbits,
    const char *cellt, const char *eofformat
) {
    int c;
    if (*membits != '\0') fprintf(outf, "#define MEMBITS %s\n", membits);
    if (*cellbits != '\0') fprintf(outf, "#define CELLBITS %s\n", cellbits);
    if (*cellt != '\0') fprintf(outf, "#define CELL_T %s\n", cellt);
    if (*eofformat != '\0') fprintf(outf, "#define EOF_FORMAT%s\n", eofformat);

    fputs("#include \"brainfuck.h\"\n", outf);
    while ( (c = getc(inf)) != EOF) {
        switch (c) {
        case '+': fputs("INC ", outf); break;
        case '-': fputs("DEC ", outf); break;
        case '>': fputs("IPT ", outf); break;
        case '<': fputs("DPT ", outf); break;
        case '[': fputs("JNZ ", outf); break;
        case ']': fputs("JZR ", outf); break;
        case '.': fputs("PUT ", outf); break;
        case ',': fputs("GET ", outf); break;
        }
    }
    fputs("JZR\n", outf);
}

static void pexit(const char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}

static void pusage(const char *binname)
{
    fprintf(stderr, 
            "Usage: %s [OPTIONS] [FILE]\nConvert brainfuck programs to brainfuck.h format\n\n"\
            "  -c [BITS]\tbit width of cells, leave unset to use all bits in the type\n"\
            "  -e [FORMAT]\tEOF format (0: return 0, -1: return -1, 1: leave unchanged)\n"\
            "  -m [BITS]\tbits of address space for memory (eg. 15 bits = 32768 cells)\n"\
            "  -o [FILE]\toutput file\n"\
            "  -t [TYPE]\tC type for cells (eg. uint32_t, \"unsigned char\")\n\n"\
            "This utility does not check for errnoneous arguments or syntax errors\n"\
            "If no input or output file is specified, stdin and stdout are used respectively\n",
            binname);
    exit(EXIT_FAILURE);
}
