#include "room.h"

Room::Room(int capacity, int time)
{
    roomCapacity = capacity;
    traversalTime = time;
    cout << "Created room with capacity " << capacity << " and traversal time of " << time << " seconds." << endl;
}
