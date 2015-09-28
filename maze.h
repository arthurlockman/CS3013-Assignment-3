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

using namespace std;

class Rat;
class Room;

class Maze
{
private:
    int maxRats;
    int maxRooms;
    time_t mazeStartTime;
public:
    Maze(string configfile, int maxrats, int maxrooms);
    vector<Room> rooms;
    vector<Rat> rats;
    int getTimeDiffSeconds();
};

#endif

