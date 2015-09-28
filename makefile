all: main

main: main.o room.o rat.o maze.o
	g++ main.o room.o rat.o maze.o -lrt -lpthread -o main

main.o: main.cpp room.h rat.h maze.h
	g++ -std=c++0x -c main.cpp

room.o: room.h room.cpp rat.h
	g++ -std=c++0x -c room.cpp

rat.o: rat.h rat.cpp room.h
	g++ -std=c++0x -c rat.cpp

maze.o: maze.h maze.cpp room.h
	g++ -std=c++0x -c maze.cpp

clean:
	rm maze.o rat.o room.o main.o main
