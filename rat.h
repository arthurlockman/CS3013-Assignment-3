#ifndef RAT_H
#define RAT_H

#include <pthread.h>
#include <iostream>
#include "maze.h"
#include "room.h"

using namespace std;

class Maze;
class Room;
class Rat
{
private:
    pthread_t _thread;
    int id;
    Maze * maze;
    Room * startingRoom;
    static void * StartThreadFunction(void * rat)
    {
        ((Rat *)rat)->Traverse();
        return NULL;
    };
protected:
    void * Traverse();
public:
    Rat(int ratID, Maze * m, Room * r);
    virtual ~Rat() {};
    bool StartThread();
    bool JoinThread();
};
#endif

