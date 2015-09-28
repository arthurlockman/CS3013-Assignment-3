#include "rat.h"

Rat::Rat(int ratID, Maze * m, Room * r)
{
    id = ratID;
    maze = m;
    startingRoom = r;
    cout << "Rat " << id << " created." << endl;
}

bool Rat::StartThread()
{
    //return (pthread_create(&_thread, NULL, &(this->Traverse), &id) == 0);
    return false;
}

