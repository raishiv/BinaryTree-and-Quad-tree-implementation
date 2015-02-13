all:PRprog
PRprog: main.o quadTree.o Bst.o
	g++ main.o quadTree.o Bst.o  -o PRprog
quadTree.o: quadTree.cpp quadTree.h
	g++ -c quadTree.cpp

main.o: main.cpp quadTree.h Bst.h
	g++ -c main.cpp

Bst.o: Bst.cpp Bst.h
	g++ -c Bst.cpp

clean:
	rm -rf *o PRprog
