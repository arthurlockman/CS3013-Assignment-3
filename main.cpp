#include "room.h"
#include "maze.h"
#include "rat.h"

int main(int argc, char ** argv)
{
    if (argc == 3 && (argv[2][0] == 'i' || argv[2][0] == 'd' || argv[2][0] == 'n') && atoi(argv[1]) <= MAXRATS)
    {
        int rats = atoi(argv[1]);
        rats = (rats > MAXRATS) ? MAXRATS : rats;
        Maze maze("./rooms", rats, MAXROOMS, argv[2][0]);
        maze.run();
    }
    else
    {
        cout << "Usage: ./maze [rats (0-" << MAXRATS << ")] [algorithm ([i]n order, [d]istributed, or [n]on-blocking)]" << endl;
        exit(0);
    }
}
