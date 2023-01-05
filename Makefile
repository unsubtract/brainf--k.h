# CC =
# CFLAGS =

all: mkbfhsrc tests
mkbfhsrc: mkbfhsrc.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	rm -f mkbfhsrc
