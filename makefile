# makefile

array.out: array.o main.o mainFuncs.o
	g++ $^ -std=c++11 -o $@
clean:
	/bin/rm -f *.o array.out
