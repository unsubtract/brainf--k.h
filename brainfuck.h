/* brainfuck.h 1.0.0 - Make your brainfuck code buildable as C (sort of)!
 * By unsubtract, ISC license, see README.md */
#ifndef BRAINFUCK_H__
#define BRAINFUCK_H__ "1.0.0"

#include <stdint.h>
#include <stdio.h>

#ifndef BRAINFUCK_MEMSIZE
    #define BRAINFUCK_MEMSIZE 30000
#endif // BRAINFUCK_MEMSIZE

// How big are the cells (bytes)?
#ifndef BRAINFUCK_CELLSIZE
    #define BRAINFUCK_CELLSIZE 1
#endif // BRAINFUCK_CELLSIZE
#if BRAINFUCK_CELLSIZE == 1
    #define BRAINFUCK_CELL uint8_t
#elif BRAINFUCK_CELLSIZE == 2
    #define BRAINFUCK_CELL uint16_t
#elif BRAINFUCK_CELLSIZE == 4
    #define BRAINFUCK_CELL uint32_t
#elif BRAINFUCK_CELLSIZE == 8
    #define BRAINFUCK_CELL uint64_t
#else
    #error "Invalid BRAINFUCK_CELLSIZE, please select 1, 2, 4 or 8 bytes."
#endif
typedef BRAINFUCK_CELL cell;
// </How big are the cells (bytes)?>

// Instructions
#define A ++*p;           // +
#define S --*p;           // -
#define N  ++p;           // >
#define P  --p;           // <
#define L while (*p) {    // [
#define C }               // ]
#define O putchar(*p);    // .
#define I *p = getchar(); // ,

#define E return 0; }     // End of program
// </Instructions>

// Start of program
int main(void) {
    cell m[sizeof(cell) * BRAINFUCK_MEMSIZE] = {0};
    cell *p = m;

#endif // BRAINFUCK_H__
