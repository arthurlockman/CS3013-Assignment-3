#ifndef ROOM_H
#define ROOM_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <semaphore.h>

using namespace std;
class Room
{
private:
    int roomCapacity;
    int traversalTime;
    int roomID;
public:
    Room(int id, int capacity, int time);
    sem_t door;
};

#endif
