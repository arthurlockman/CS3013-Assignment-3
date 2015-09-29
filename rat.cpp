#include "rat.h"

Rat::Rat(int ratID, Maze * m, int room)
{
    id = ratID;
    maze = m;
    startingRoom = room;
    cout << "Rat " << id << " created, starting in room " <<
        startingRoom << "." << endl;
}

bool Rat::StartThread()
{
    return (pthread_create(&_thread, NULL, &this->StartThreadFunction, this) == 0);
}

void * Rat::Traverse(void * rat)
{
    int idx = ((Rat *)rat)->startingRoom;
    int visited = 0;
    Room * r;
    while ((unsigned long)visited < maze->rooms.size())
    {
        /* cout << "Rat " << ((Rat *)rat)->id << " starting in room " << idx << endl; */
        r = &maze->rooms.at(idx);
        r->EnterRoom(this);
        int entryTime = maze->getTimeDiffSeconds();
        sleep(r->getTraversalTime());
        r->LeaveRoom(this);
        int exitTime = maze->getTimeDiffSeconds();
        /* cout << "Rat " << ((Rat *)rat)->id << " leaving room " << idx << endl; */
        maze->addToLogbook(idx, ((Rat *)rat)->id, entryTime, exitTime);
        visited++;
        idx++;
        if ((unsigned long)idx > maze->rooms.size() - 1)
            idx = 0;
    }
    ((Rat *)rat)->timeToComplete = maze->getTimeDiffSeconds();
    return NULL;
}

bool Rat::JoinThread()
{
    return (pthread_join(_thread, NULL) == 0);
}

int Rat::getTime()
{
    return timeToComplete;
}
