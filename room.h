#ifndef ROOM_H
#define ROOM_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <semaphore.h>
#include "rat.h"

using namespace std;

class Rat;

class Room
{
private:
    int roomCapacity;
    int traversalTime;
    int roomID;
public:
    Room(int id, int capacity, int time);
    sem_t door;
    void EnterRoom(Rat * rat);
    void LeaveRoom(Rat * rat);
    int TryToEnterRoom(Rat * rat);
    int getID();
    int getTraversalTime();
    int getCapacity();
};

#endif
