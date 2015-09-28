#include "rat.h"
#include "maze.h"

Maze::Maze(string configfile, int maxrats, int maxrooms)
{
    maxRats = maxrats;
    maxRooms = maxrooms;
    ifstream file;
    file.open(configfile.c_str(), ios::in);
    cout << "Creating new maze with a maximum of " << maxrooms << " rooms and " << maxrats << " rats." << endl;
    cout << "Opened config file at " << configfile << endl;

    int capacity, time, numrooms = 0;
    string str;
    while (getline(file, str) && (numrooms < maxRooms))
    {
        char *s = strtok((char *)str.c_str(), " ");
        capacity = atoi(s);
        s = strtok(NULL,  " ");
        time = atoi(s);
        numrooms++;
        Room r(capacity, time);
        rooms.push_back(r);
    }
    file.close();
}

