#include "rat.h"
#include "maze.h"

/**
 * Constructs the maze object.
 * @param configfile The file to read in the room configuration from.
 * @param maxrats The maximum number of allowable rats in the maze.
 * @param maxrooms The maximum number of allowable rooms.
 * @param alg The algorithm to use (n, i, or d)
 */
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
        //If there are more or less data points per line, bad file
        if (sscanf((char *)str.c_str(), "%i %i", &capacity, &delayTime) != 2)
        {
            cerr << "Bad description file!" << endl;
            exit(1);
        }
        Room r(numrooms, capacity, delayTime); //create and add room to list of rooms
        rooms.push_back(r);
        numrooms++;
    }
    file.close();

    cout << "Spawning " << maxRats << " rats..." << endl;
    int mode = (alg == 'n') ? 1 : 0;
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
        }
        else
        {
            rm = i;
        }
        Rat r(i, this, rm, mode); //Create and add rats to list of rats.
        rats.push_back(r);
    }
    sem_init(&vbSem, 0, 1);
}

/**
 * Maze destructor. Handles cleanup, mainly destroying all of 
 * the semaphores created by the program properly.
 */
Maze::~Maze()
{
    for (int i = 0; (unsigned long)i < rooms.size(); i++) //Destroy all semaphores.
    {
        Room r = rooms.at(i);
        sem_destroy(&r.door);
    }
    sem_destroy(&vbSem);
}

/**
 * Get the difference in seconds between now and when the maze
 * traversal started. Simplifies log book entering in the rat class.
 */
int Maze::getTimeDiffSeconds()
{
    time_t t = time(NULL);
    return (int)difftime(t, mazeStartTime);
}

/**
 * Run the maze. This starts and kills all of the rats, and 
 * then prints out all of the results of the maze traversal.
 */
void Maze::run()
{
    cout << "\nLETTING LOOSE THE RATS...\n" << endl;
    mazeStartTime = time(NULL);
    for (int i = 0; (unsigned long)i < rats.size(); i++)
    {
        rats.at(i).StartThread();
    }
    for (int i = 0; (unsigned long)i < rats.size(); i++)
    {
        rats.at(i).JoinThread();
    }
    int idealTime = 0;
    for (int i = 0; (unsigned long)i < rooms.size(); i++)
    {
        cout << "Room " << i << " [" << rooms.at(i).getTraversalTime() << " " << rooms.at(i).getCapacity() << "]: ";
        idealTime += rooms.at(i).getTraversalTime();
        for (int j = 0; (unsigned long)j < rats.size(); j++)
        {
            cout << RoomVB[i][j].iRat << " " << RoomVB[i][j].tEntry << " " << RoomVB[i][j].tDep << "; ";
        }
        cout << endl;
    }
    idealTime *= rats.size();
    int totaltime = 0;
    for (int i = 0; (unsigned long)i < rats.size(); i++)
    {
        cout << "Rat " << i << " completed maze in " << rats.at(i).getTime() << " seconds." << endl;
        totaltime += rats.at(i).getTime();
    }
    cout << "Total traversal time: " << totaltime << " seconds, compared to ideal time: " << idealTime << " seconds." << endl;
}

/**
 * Adds a data point to the specified logbook.
 * @param room The room to add an entry for.
 * @param ratID The rat to add an entry for.
 * @param timeEntry The time that the rat entered the room.
 * @param timeDep the time that the rat lef the room.
 */
void Maze::addToLogbook(int room, int ratID, int timeEntry, int timeDep)
{
    sem_wait(&vbSem);
    RoomVB[room][ratID].iRat = ratID;
    RoomVB[room][ratID].tEntry = timeEntry;
    RoomVB[room][ratID].tDep = timeDep;
    VisitorCount[room] += 1;
    sem_post(&vbSem);
}

/**
 * Get the room in the maze with the "lowest cost". This is 
 * found by looping through each room and finding the one that
 * reports the lowest cost, and then returning that one's ID.
 * This also takes into account which rooms the rat has 
 * previously visited.
 * @param visited An array of integers representing room IDs
 * that the rat has already visited.
 * @return An int, the room ID of the cheapest room in the maze.
 */
int Maze::getCheapestRoom(int * visited)
{
    int room;
    int cost = 10000;
    for (unsigned long i = 0; i < rooms.size(); i++)
    {
        if (visited[i] != 1)
        {
            int tmpcost = rooms.at(i).getCost();
            if (tmpcost < cost)
            {
                room = i;
                cost = tmpcost;
            }
        }
    }
    return room;
}
