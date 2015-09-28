all: main

main: main.o room.o rat.o maze.o
	g++ main.o room.o rat.o maze.o -lrt -lpthread -o main

main.o: main.cpp room.h rat.h maze.h
	g++ -std=c++11 -c main.cpp

room.o: room.h room.cpp rat.h
	g++ -std=c++11 -c room.cpp

rat.o: rat.h rat.cpp room.h
	g++ -std=c++11 -c rat.cpp

maze.o: maze.h maze.cpp room.h
	g++ -std=c++11 -c maze.cpp

clean:
	rm maze.o rat.o room.o main.o main
