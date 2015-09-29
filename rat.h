#ifndef RAT_H
#define RAT_H

#include <pthread.h>
#include <iostream>
#include "maze.h"
#include "room.h"
#include <unistd.h>

using namespace std;

class Maze;
class Room;
class Rat
{
private:
    pthread_t _thread;
    int id;
    Maze * maze;
    int startingRoom;
    int timeToComplete;
    int traversalMode; //0 is normal, 1 is non-blocking
    static void * StartThreadFunction(void * rat)
    {
        return ((Rat *)rat)->Traverse(rat);
    };
protected:
    void * Traverse(void * rat);
public:
    Rat(int ratID, Maze * m, int room, int mode);
    virtual ~Rat() {};
    bool StartThread();
    bool JoinThread();
    int getTime();
};
#endif

