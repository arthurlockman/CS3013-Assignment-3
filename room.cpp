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
