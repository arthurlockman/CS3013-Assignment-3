#ifndef RAT_H
#define RAT_H

#include <pthread.h>
#include <iostream>
#include "maze.h"

using namespace std;
class Rat
{
private:
    pthread_t _thread;
    int id;
    Maze * maze;
    static void * StartThreadFunction(void * rat)
    {
        ((Rat *)rat)->Traverse();
        return NULL;
    };
protected:
    void * Traverse();
public:
    Rat(int ratID, Maze * m)
    {
        id = ratID;
        maze = m;
    };
    virtual ~Rat() {};
    bool StartThread();
    bool JoinThread();
};
#endif

