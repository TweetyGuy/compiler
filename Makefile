IDIR = include
CC = gcc
CFLAGS = -I$(IDIR) -I$(IDIR)/frontend -I$(IDIR)/backend 

ODIR = bin

_DEPS =	frontend/lexer.h frontend/hash.h driver.h errors.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJS = frontend/lexer.o frontend/hash.o driver.o errors.o
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compiler: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean test

clean:
	rm -f compiler
	rm -f $(ODIR)/*.o
	rm -f $(ODIR)/frontend/*.o
	rm -f $(ODIR)/backend/*.o

test: compiler
	./$<
