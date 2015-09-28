#ifndef ROOM_H
#define ROOM_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
class Room
{
private:
    int roomCapacity;
    int traversalTime;
public:
    Room(int capacity, int time);
};

#endif
