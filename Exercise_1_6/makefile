IDIR=inc
CC=gcc-12
PROG_NAME = Ex_1_6
CFLAGS=-I$(IDIR) -g -Wall -lm -O3
BDIR = bin

ODIR=obj
LDIR=lib

_DEPS = read_data.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o read_data.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/$(PROG_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
