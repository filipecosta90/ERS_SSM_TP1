 ODIR=source
LDIR =../lib

#compilador
CC=gcc-5
#flags
CFLAGS= -Wall -Wextra -g -O2 -O3

#nome do executável
EXECUTABLE=freq_anl

_OBJ = frequency_analysor.o readLineSO.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = readLine.h
DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
