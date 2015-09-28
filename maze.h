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

using namespace std;
class Rat;

class Maze
{
private:
    int maxRats;
    int maxRooms;
public:
    Maze(string configfile, int maxrats, int maxrooms);
    vector<Room> rooms;
    vector<Rat> rats;
};

#endif

