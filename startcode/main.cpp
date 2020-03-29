
/**********************************
 * Program: main.cpp
 * Author: LiangyuNie
 * Date: 03/27/2020
 * Description: 
 *  1. usesection 2.1 algrithm to finish this problem
 *  *  2. The problem is its hard to read column and row of map when I use dynamic array
 *  3. read the maze and out
 *      follow the Breadcrumb，Trail，MazeSolver,and main
 *  5. for the Milestone 3，Trail Breadcrumb，
 *      from the start to end,output 2 adjacent stale which is false and compare them to get the direction
 *  6. for the Milestone 4，use the advice in milestone4.hodynamic allocation the large of arrage
 *     cosider the maze's dimension is not too big so I set MAZE_DIM=200，
 *      for the Breadcrumb in Trail,length is TRAIL_ARRAY_MAX_SIZE=(MAZE_DIM * MAZE_DIM)
 ****************************************/
#include <iostream>
#include <string>
#include <string.h>
#include "Types.h"
#include "MazeSolver.h"
#include "milestone4.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail *solution);

// Print out walking solution
void printWalkingDirections(Trail *solution);

int main(int argc, char **argv)
{
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testBreadcrumb();
    // testTrail();
    // std::cout << "DONE TESTING" << std::endl
    //           << std::endl;

    // Load Maze from stdin
    Maze maze;
    maze = make_maze(MAZE_DIM, MAZE_DIM);
    readMazeStdin(maze);
    // Solve using MazeSolver
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    MazeSolver *solver = new MazeSolver();
    Trail *solution = nullptr;
    solver->solve(maze);
    solution = solver->getSolution();

    // Print Maze to stdout
    printMazeStdout(maze, solution);

    printWalkingDirections(solution);
    delete solver;
    delete_maze(maze, MAZE_DIM, MAZE_DIM);

    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze)
{
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
    int y = 0, x = 0;
    char ch;
    while ((ch = std::cin.get()) != -1)
    {
        maze[y][x] = ch;
        if (ch == '\n')
        {
            y++;
            x = 0;
        }
        else
            x++;
    }
    maze[y][x] = 0;
}

void printMazeStdout(Maze maze, Trail *solution)
{
    int y = 0, x = 0;
    for (y = 0;; y++)
    {
        if (maze[y][0] == 0)
            break;
        for (x = 0;; x++)
        {
            if (maze[y][x] == '\r' || maze[y][x] == '\n')
                break;
            // if there exits a breadcrumb in solution
            if (solution->contains(x, y) && maze[y][x] != 'S' && maze[y][x] != 'E')
            {
                for (int k = 0; k < solution->size(); k++)
                {
                    Breadcrumb *now = solution->getPtr(k);
                    if (now->getX() == x && now->getY() == y)
                    {
                        // if the breadcrumb is set false
                        if (now->isStale() == false)
                        {
                            std::cout << "*";
                        }
                        else
                            std::cout << maze[y][x];
                        break;
                    }
                }
            }
            else
                std::cout << maze[y][x];
        }
        std::cout << "\r" << std::endl;
    }
}

void printWalkingDirections(Trail *solution)
{
    Breadcrumb *last = nullptr;
    for (int i = 0; i < solution->size(); i++)
    {
        Breadcrumb *cur = solution->getPtr(i);
        if (cur->isStale() == true)
            continue;
        if (last == nullptr)
        {
            last = cur;
            continue;
        }
        // compare cur with last to get direction
        // North
        if (cur->getY() - last->getY() == -1)
        {
            std::cout << "north" << std::endl;
        }
        // South
        else if (cur->getY() - last->getY() == 1)
        {
            std::cout << "south" << std::endl;
        }
        // West
        else if (cur->getX() - last->getX() == -1)
        {
            std::cout << "west" << std::endl;
        }
        // East
        else if (cur->getX() - last->getX() == 1)
        {
            std::cout << "east" << std::endl;
        }
        last = cur;
    }
}

void testBreadcrumb()
{
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb *breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;
}

void testTrail()
{
    std::cout << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail *trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb *b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0, 0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1, 1) << std::endl;

    // Add second breadcrumb
    Breadcrumb *b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0, 0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1, 1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb *getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl;

    // Print out the trail
    std::cout << "PRINTING OUT A TRAIL IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
