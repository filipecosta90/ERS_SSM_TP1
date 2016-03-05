
CXX = g++-5

#flags

CPPFLAGS= -O2 -O3 -std=c++11


cpp: freq_analyse.o 
	$(CXX) $(CPPFLAGS) -o freq_anl freq_analyse.cpp FileCompress.cpp FileBlock.cpp SymbolTable.cpp Symbol.cpp

all: cpp

.PHONY: clean
clean:
	rm  *.o && rm rm freq_anl
