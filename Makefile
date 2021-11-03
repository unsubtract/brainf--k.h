.POSIX:
CC = cc
# No optimizations by default, super slow brainfuck instructions!
CFLAGS =

all: convert demos
convert: convert.c
	$(CC) $(CFLAGS) $@.c -o $@
demos: convert bitwidth calculator mandelbrot PI16 yoruemom

# Demos
bitwidth.c: demos/bitwidth.b convert
	cat demos/$*.b | ./convert > $@
bitwidth: bitwidth.c brainfuck.h
	$(CC) $(CFLAGS) $@.c -o $@

calculator.c: demos/calculator.b convert
	cat demos/$*.b | ./convert 255 > $@
calculator: calculator.c brainfuck.h
	$(CC) $(CFLAGS) $@.c -o $@

mandelbrot.c: demos/mandelbrot.b convert
	cat demos/$*.b | ./convert > $@
mandelbrot: mandelbrot.c brainfuck.h
	$(CC) $(CFLAGS) $@.c -o $@

PI16.c: demos/PI16.b convert
	cat demos/$*.b | ./convert 65535 > $@
PI16: PI16.c brainfuck.h
	$(CC) $(CFLAGS) $@.c -o $@

yoruemom.c: demos/yoruemom.b convert
	cat demos/$*.b | ./convert > $@
yoruemom: yoruemom.c brainfuck.h
	$(CC) $(CFLAGS) $@.c -o $@
# /Demos

clean:
	rm -f convert bitwidth.c bitwidth calculator.c calculator mandelbrot.c mandelbrot PI16.c PI16 yoruemom.c yoruemom
