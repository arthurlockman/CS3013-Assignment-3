#include "rat.h"
#include "maze.h"

Maze::Maze(string configfile, int maxrats, int maxrooms, char alg)
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
        int rm;
        if (alg == 'i')
        {
            rm = 0;
        }
        else if ((unsigned long)maxRats > rooms.size())
        {
            rm = i % rooms.size();
        } else
        {
            rm = i;
        }
        Rat r(i, this, rm);
        rats.push_back(r);
    }
    sem_init(&vbSem, 0, 1);
}

Maze::~Maze()
{
    for (int i = 0; (unsigned long)i < rooms.size(); i++) //Destroy all semaphores.
    {
        Room r = rooms.at(i);
        sem_destroy(&r.door);
    }
    sem_destroy(&vbSem);
}

int Maze::getTimeDiffSeconds()
{
    time_t t = time(NULL);
    return (int)difftime(t, mazeStartTime);
}

void Maze::run()
{
    //TODO: Traverse maze here.
    mazeStartTime = time(NULL);
    for (int i = 0; (unsigned long)i < rats.size(); i++)
    {
        rats.at(i).StartThread();
    }
    for (int i = 0; (unsigned long)i < rats.size(); i++)
    {
        rats.at(i).JoinThread();
    }
    for (int i = 0; (unsigned long)i < rooms.size(); i++)
    {
        for (int j = 0; (unsigned long)j < rats.size(); j++)
        {
            cout << "Room " << i << " visited by rat " << RoomVB[i][j].iRat
                << ", entered at " << RoomVB[i][j].tEntry << " and left at "
                << RoomVB[i][j].tDep << "." << endl;
        }
    }
}

void Maze::addToLogbook(int room, int ratID, int timeEntry, int timeDep)
{
    sem_wait(&vbSem);
    RoomVB[room][ratID].iRat = ratID;
    RoomVB[room][ratID].tEntry = timeEntry;
    RoomVB[room][ratID].tDep = timeDep;
    VisitorCount[room] += 1;
    sem_post(&vbSem);
}

