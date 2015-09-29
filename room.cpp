#include "room.h"

Room::Room(int id, int capacity, int time)
{
    roomID = id;
    roomCapacity = capacity;
    traversalTime = time;
    sem_init(&door, 0, capacity);
    cout << "Created room " << id << " with capacity " << capacity
        << " and traversal time of " << time << " seconds." << endl;
}


void Room::EnterRoom(Rat * rat)
{
    sem_wait(&door);
}

void Room::LeaveRoom(Rat * rat)
{
    sem_post(&door);
}

int Room::TryToEnterRoom(Rat * rat)
{
    return sem_trywait(&door);
}

int Room::getID()
{
    return roomID;
}

int Room::getTraversalTime()
{
    return traversalTime;
}

int Room::getCapacity()
{
    return roomCapacity;
}

int Room::getCost()
{
    int emptySlots;
    sem_getvalue(&door, &emptySlots);
    emptySlots = (emptySlots < 0) ? 0 : emptySlots;
    int taken = roomCapacity - emptySlots;
    return taken * traversalTime;
}
