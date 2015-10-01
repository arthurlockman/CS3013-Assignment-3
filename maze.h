#ifndef MAZE_H
#define MAZE_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include "room.h"
#include <fstream>
#include <cstring>
#include "rat.h"
#include <time.h>

#define MAXRATS 5
#define MAXROOMS 8

using namespace std;

typedef struct{
    int iRat; //rat identifier
    int tEntry; //Time of rat entry
    int tDep; //time of rat departure
} vbentry;

class Rat;
class Room;

class Maze
{
private:
    int maxRats; //Max number of rats in maze.
    int maxRooms; //Max number of rooms in maze.
    time_t mazeStartTime; //Start time of all rats traversal.
    vbentry RoomVB[MAXROOMS][MAXRATS]; //Visitors book
    int VisitorCount[MAXROOMS]; //Count of visitors for each room
    sem_t vbSem; //Semaphore to control access to visitors book
public:
    Maze(string configfile, int maxrats, int maxrooms, char alg);
    ~Maze();
    vector<Room> rooms;
    vector<Rat> rats;
    int getTimeDiffSeconds();
    void run();
    void addToLogbook(int room, int ratID, int timeEntry, int timeDep);
    int getCheapestRoom(int * visited);
};

#endif

