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
    int iRat;
    int tEntry;
    int tDep;
} vbentry;

class Rat;
class Room;

class Maze
{
private:
    int maxRats;
    int maxRooms;
    time_t mazeStartTime;
    vbentry RoomVB[MAXROOMS][MAXRATS];
    int VisitorCount[MAXROOMS];
    sem_t vbSem;
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

