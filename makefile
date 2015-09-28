all: main

main: main.o room.o rat.o maze.o
	g++ main.o room.o rat.o maze.o -o main

main.o: main.cpp room.h rat.h maze.h
	g++ -c main.cpp

room.o: room.h room.cpp rat.h
	g++ -c room.cpp

rat.o: rat.h rat.cpp room.h
	g++ -c rat.cpp

maze.o: maze.h maze.cpp room.h
	g++ -c maze.cpp

clean:
	rm maze.o rat.o room.o main.o main
