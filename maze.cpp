#include "rat.h"
#include "maze.h"

Maze::Maze(string configfile, int maxrats, int maxrooms)
{
    maxRats = maxrats;
    maxRooms = maxrooms;
    ifstream file;
    file.open(configfile.c_str(), ios::in);
    if (!file)
    {
        cerr << "File " << configfile << " could not be opened. Exiting..." << endl;
        exit(0);
    }
    cout << "Creating new maze with a maximum of " << maxrooms << " rooms and " << maxrats << " rats." << endl;
    cout << "Opened config file at " << configfile << endl;

    int capacity, delayTime, numrooms = 0;
    string str;
    while (getline(file, str) && (numrooms < maxRooms))
    {
        char *s = strtok((char *)str.c_str(), " ");
        capacity = atoi(s);
        s = strtok(NULL,  " ");
        delayTime = atoi(s);
        Room r(numrooms, capacity, delayTime);
        rooms.push_back(r);
        numrooms++;
    }
    file.close();

    cout << "Spawning " << maxRats << " rats..." << endl;
    for (int i = 0; i < maxRats; i++)
    {
        Rat r(i, this);
        rats.push_back(r);
    }
    //TODO: Traverse maze here.
    mazeStartTime = time(NULL);

    for (int i = 0; (unsigned long)i < rooms.size(); i++) //Destroy all semaphores.
    {
        Room r = rooms.at(i);
        sem_destroy(&r.door);
    }
}


int Maze::getTimeDiffSeconds()
{
    time_t t = time(NULL);
    return (int)difftime(t, mazeStartTime);
}

