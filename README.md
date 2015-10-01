CS 3013 Assignment 3
====================

This assignment requires the use of pthreads to simulate a maze with many rats moving through it. The objective of the assignment is to gain experience using pthreads and resource synchronization.

The implementation presented in this submission is done in C++, with each physical object (rat, room, maze) represented by a class. The rat class contains the rat ID and the pthread that the rat uses to traverse the maze. All threaded operations take place within the rat class. The room class contains essentially only the semaphore that defines the room access, called <code>door</code> in the implementation. Finally, the <code>maze</code> class contains the network of rooms and spawns and starts each of the rats. For more details on the implementation, see the comments given in the code for each of the classes.

Compiling
---------

To compile the code, simply type the following in the build folder:

    make

To clean the compiled objects, type:

    make clean

PLEASE NOTE: This program will only compile on CCC1 due to the fact that the other CCC machines are running ancient versions of g++.

Running
-------
To run the program, in the directory type:

    ./maze [number of rats] [algorithm]

The number of rats is an integer between 1 and 5. There are three modes that the program can be run in: in-order, distributed, and non-blocking. These modes are described below.

    ./maze 5 i

The command above runs the maze in in-order mode. In this mode, the rats are all started in room 0 of the maze, and proceed in order through the maze. This mode exhibits the worst performance, as shown below:

    Creating new maze with a maximum of 8 rooms and 5 rats.
    Opened config file at ./rooms
    Created room 0 with capacity 3 and traversal time of 1 seconds.
    Created room 1 with capacity 2 and traversal time of 2 seconds.
    Created room 2 with capacity 1 and traversal time of 2 seconds.
    Spawning 5 rats...
    Rat 0 created, starting in room 0.
    Rat 1 created, starting in room 0.
    Rat 2 created, starting in room 0.
    Rat 3 created, starting in room 0.
    Rat 4 created, starting in room 0.

    LETTING LOOSE THE RATS...

    Room 0 [1 3]: 0 0 1; 1 0 1; 2 0 1; 3 1 2; 4 1 2;
    Room 1 [2 2]: 0 1 3; 1 1 3; 2 3 5; 3 5 7; 4 3 5;
    Room 2 [2 1]: 0 5 7; 1 3 5; 2 7 9; 3 11 13; 4 9 11;
    Rat 0 completed maze in 7 seconds.
    Rat 1 completed maze in 5 seconds.
    Rat 2 completed maze in 9 seconds.
    Rat 3 completed maze in 13 seconds.
    Rat 4 completed maze in 11 seconds.
    Total traversal time: 45 seconds, compared to ideal time: 25 seconds.

The next possible mode is the distributed mode, given below:

    ./maze 5 d

This mode starts the rats each in different rooms according to their ID. If there are up to as many rats as rooms, then each rat will start in a different room. If there are more rats than rooms, then each rat will start in the room number corresponding to its own ID modulo the number of rooms in the maze. It proceeds through the maze from this initial point in the same manner as the in-order algorithm. This provides better performance than the in-order algorithm, shown below:

    Creating new maze with a maximum of 8 rooms and 5 rats.
    Opened config file at ./rooms
    Created room 0 with capacity 3 and traversal time of 1 seconds.
    Created room 1 with capacity 2 and traversal time of 2 seconds.
    Created room 2 with capacity 1 and traversal time of 2 seconds.
    Spawning 5 rats...
    Rat 0 created, starting in room 0.
    Rat 1 created, starting in room 1.
    Rat 2 created, starting in room 2.
    Rat 3 created, starting in room 0.
    Rat 4 created, starting in room 1.

    LETTING LOOSE THE RATS...

    Room 0 [1 3]: 0 0 1; 1 4 5; 2 2 3; 3 0 1; 4 10 11;
    Room 1 [2 2]: 0 2 4; 1 0 2; 2 4 6; 3 2 4; 4 0 2;
    Room 2 [2 1]: 0 6 8; 1 2 4; 2 0 2; 3 4 6; 4 8 10;
    Rat 0 completed maze in 8 seconds.
    Rat 1 completed maze in 5 seconds.
    Rat 2 completed maze in 6 seconds.
    Rat 3 completed maze in 6 seconds.
    Rat 4 completed maze in 11 seconds.
    Total traversal time: 36 seconds, compared to ideal time: 25 seconds.

The final mode of operation is the non-blocking method.

    ./maze 5 n

In the other two algorithms, the rats will wait for an open spot in the next room of the maze. In the non-blocking algorithm, a rat will attempt to enter a room and upon being denied entry will move on to a different room and come back to that room later. A more detailed description of the algorithm used can be seen in the <code>rat</code> class. A sample run of this algorithm can be seen below.

    Creating new maze with a maximum of 8 rooms and 5 rats.
    Opened config file at ./rooms
    Created room 0 with capacity 3 and traversal time of 1 seconds.
    Created room 1 with capacity 2 and traversal time of 2 seconds.
    Created room 2 with capacity 1 and traversal time of 2 seconds.
    Spawning 5 rats...
    Rat 0 created, starting in room 0.
    Rat 1 created, starting in room 1.
    Rat 2 created, starting in room 2.
    Rat 3 created, starting in room 0.
    Rat 4 created, starting in room 1.

    LETTING LOOSE THE RATS...

    Room 0 [1 3]: 0 0 1; 1 2 3; 2 2 3; 3 0 1; 4 4 5;
    Room 1 [2 2]: 0 2 4; 1 0 2; 2 4 6; 3 2 4; 4 0 2;
    Room 2 [2 1]: 0 6 8; 1 8 10; 2 0 2; 3 4 6; 4 2 4;
    Rat 0 completed maze in 8 seconds.
    Rat 1 completed maze in 10 seconds.
    Rat 2 completed maze in 6 seconds.
    Rat 3 completed maze in 6 seconds.
    Rat 4 completed maze in 5 seconds.
    Total traversal time: 35 seconds, compared to ideal time: 25 seconds.

As can be seen in the above example, the non-blocking algorithm provides better execution time than the others, running in 1 fewer seconds than the distributed algorithm.
