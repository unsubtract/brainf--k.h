/* brainfuck.h 3.0.0 - build brainfuck in a C compiler (not recommended though)
 * By unsubtract, MIT license, see README.md */
#ifndef BRAINFUCK_H
#define BRAINFUCK_H 2

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* public macros */
#ifndef MEMBITS
 #define MEMBITS 15
#endif

/* #ifndef CELLBITS
 *  #define CELLBITS 8
 * #endif */

#ifndef CELL_T
  #define CELL_T uint8_t
#endif

#ifndef EOF_FORMAT
  #define EOF_FORMAT 0
#endif
/* */

#ifdef CELLBITS
  #define CELL_MASK_ (((CELL_T)1 << CELLBITS) - 1) /* cast forces unsigned */
#endif

#define MEM_MASK_ ((1 << MEMBITS) - 1)

#define INC_MASKED /* + */ (*p) = (*p + 1) & CELL_MASK_;
#define DEC_MASKED /* - */ (*p) = (*p - 1) & CELL_MASK_;

#define INC_OVERFLOW /* + */ *p += 1;
#define DEC_OVERFLOW /* - */ *p -= 1;

#ifdef CELLBITS
  #define INC INC_MASKED
  #define DEC DEC_MASKED
#else
  #define INC INC_OVERFLOW
  #define DEC DEC_OVERFLOW
#endif

/* simple cyclic buffer */
#define IPT /* > */ offset = (offset + 1) & MEM_MASK_; p = m + offset;
#define DPT /* < */ offset = (offset - 1) & MEM_MASK_; p = m + offset;

#define JNZ /* [ */ while (*p) {
#define JZR /* ] */ }

#define PUT /* . */ putchar( (int)*p ); /* cast to avoid warning */

/* , */
#define GET_ZERO_ c = getchar(); *p = (c != EOF) ? (CELL_T)c : 0;
#define GET_NEG_ c = getchar(); *p = (c != EOF) ? (CELL_T)c : CELL_MASK_;
#define GET_UNCHANGED_ c = getchar(); if (c != EOF) *p = (CELL_T)c;

#if EOF_FORMAT == 0
  #define GET GET_ZERO_
#elif EOF_FORMAT == -1
  #define GET GET_NEG_
#elif EOF_FORMAT == 1
  #define GET GET_UNCHANGED_
#else
  #define GET
  #error "Invalid EOF format (must be 0, -1 or 1)"
#endif /* */


/* inserts main function */
int main(void) {
    CELL_T m[1 << MEMBITS] = {0}, *p = m;
    size_t offset = 0;
    int c;

#endif /* BRAINFUCK_H */
