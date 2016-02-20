
CXX = g++-5
CC = gcc-5

#flags
CFLAGS= -Wall -O2 -O3

CPPFLAGS= -Wall -O2 -O3 -std=c++11

c: freq_analyse_c.o
	$(CC) $(CFLAGS) -o freq_anl_c freq_analyse_c.c

cpp: freq_analyse_cpp.o
	$(CXX) $(CPPFLAGS) -o freq_anl_cpp freq_analyse_cpp.cpp

all: c cpp

.PHONY: clean
clean:
	rm  *.o && rm freq_anl_c && rm freq_anl_cpp
