#include "room.h"
#include "maze.h"
#include "rat.h"

int main(int argc, char ** argv)
{
    if (argc == 3 && (argv[2][0] == 'i' || argv[2][0] == 'd'))
    {
        int rats = atoi(argv[1]);
        rats = (rats > MAXRATS) ? MAXRATS : rats;
        Maze maze("./rooms", rats, MAXROOMS, argv[2][0]);
        maze.run();
    }
    else
    {
        cout << "Usage: ./maze [rats] [algorithm ([i]n order or [d]istributed)]" << endl;
        exit(0);
    }
}
