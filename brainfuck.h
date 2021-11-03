/* brainfuck.h 1.0.1 - Make your brainfuck code buildable as C (sort of)!
 * By unsubtract, ISC license, see README.md */
#ifndef BRAINFUCK_H__
#define BRAINFUCK_H__ "1.0.1"

#include <limits.h>
#include <stdio.h>

#ifndef BRAINFUCK_MEMSIZE
    #define BRAINFUCK_MEMSIZE 30000
#endif /* /BRAINFUCK_MEMSIZE */

/* How big are the cells? */
#ifndef BRAINFUCK_CELLSIZE
    #define BRAINFUCK_CELLSIZE 255
#endif /* /BRAINFUCK_CELLSIZE */
#if BRAINFUCK_CELLSIZE == UCHAR_MAX
    #define BRAINFUCK_CELL unsigned char
#elif BRAINFUCK_CELLSIZE == USHRT_MAX
    #define BRAINFUCK_CELL unsigned short int
#elif BRAINFUCK_CELLSIZE == UINT_MAX
    #define BRAINFUCK_CELL unsigned int
#elif BRAINFUCK_CELLSIZE == ULONG_MAX
    #define BRAINFUCK_CELL unsigned long int
#else
    #error "Invalid BRAINFUCK_CELLSIZE,\
 please select an unsigned integer limit (see limits.h(0P))."
#endif
typedef BRAINFUCK_CELL cell;
/* /How big are the cells? */

/* Instructions */
#define A /* + */ ++(*p);
#define S /* - */ --(*p);
#define N /* > */ ++p;
#define P /* < */ --p;
#define L /* [ */ while (*p) {
#define C /* ] */ }
#define O /* . */ putchar(*p);
#define I /* , */ *p = getchar();

#define E /* End */ return 0; }
/* /Instructions */

/* Start of program */
int main(void) {
    cell m[BRAINFUCK_MEMSIZE] = {0};
    cell *p = m;

#endif /* /BRAINFUCK_H__*/
