ODIR=src
LDIR =../lib

#compilador
CC=gcc-5
#flags
CFLAGS= -Wall -Wextra -g -O2 -O3

#nome do executável
EXECUTABLE=freq_anl

_OBJ = frequency_analysor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = readSSM.h
DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o && rm freq_anl
