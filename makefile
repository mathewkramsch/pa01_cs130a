# makefile

linkedlist.out: ll/ll.o ll/main.o mainFuncs.o exceptions.o
	g++ $^ -std=c++11 -o $@
array.out: array/array.o array/main.o mainFuncs.o exceptions.o
	g++ $^ -std=c++11 -o $@
clean:
	/bin/rm -f *.o array.out linkedlist.out array/*.o ll/*.o
