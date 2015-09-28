#include "room.h"
#include "maze.h"
#include "rat.h"

#define MAXRATS 5
#define MAXROOMS 8

int main(int argc, char ** argv)
{
    if (argc == 2)
    {
        int rats = atoi(argv[1]);
        rats = (rats > MAXRATS) ? MAXRATS : rats;
        Maze maze("./room_config.txt", rats, MAXROOMS); 
    }
    else if (argc == 3)
    {
        int rats = atoi(argv[1]);
        rats = (rats > MAXRATS) ? MAXRATS : rats;
        Maze maze(argv[2], rats, MAXROOMS);
    }
    else
    {
        cout << "Usage: ./main [rats] [config_path]" << endl;
        exit(0);
    }
}
