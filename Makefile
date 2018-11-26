CC=g++
MAKE_CFLAGS=-g -pedantic -Wall -Wextra $(CFLAGS)
LFLAGS=-lncurses

PROGRAMS=test_grid main

all: $(PROGRAMS)

test_grid: test_grid.cc grid.o
	$(CC) $(MAKE_CFLAGS) $^ -o $@

main: main.cc grid.o
	$(CC) $(MAKE_CFLAGS) $^ -o $@ $(LFLAGS)

%.o: %.cc %.h
	$(CC) $(MAKE_CFLAGS) $< -c -o $@

clean:
	rm -f $(PROGRAMS) *.o
