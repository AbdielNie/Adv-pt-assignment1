
#include "MazeSolver.h"

MazeSolver::MazeSolver()
{
   // constructor
   solution = new Trail();
}

MazeSolver::~MazeSolver()
{
   // free memory
   delete solution;
}

void MazeSolver::solve(Maze maze)
{
   int sx = 0, sy = 0, ex = 0, ey = 0;
   int y = 0, x = 0;
   int row = 0, col = 0;
   while (maze[y][x])
   {
      // get start point 'S'
      if (maze[y][x] == 'S')
      {
         sx = x;
         sy = y;
      }
      // get end point 'E'
      if (maze[y][x] == 'E')
      {
         ex = x;
         ey = y;
      }
      // change to a new line
      if (maze[y][x] == '\r')
      {
         col++;
         row = x;
         y++;
         x = 0;
      }
      else if (maze[y][x] == '\n')
      {
         col++;
         row = x;
         y++;
         x = 0;
      }
      else
         x++;
   }
   int bx = sx, by = sy;
   while (true)
   {
      // loop while b is not end point 'E'
      if (bx == ex && by == ey)
         break;
      // Add a breadcrumb for b to the end of the trail
      if (!solution->contains(bx, by))
      {
         solution->addCopy(new Breadcrumb(bx, by, false));
      }
      // Look for a place to go next
      int i;
      for (i = 0; i < 4; i++)
      {
         int to_x = 0, to_y = 0;
         if (i == 0)
         {
            to_x = bx, to_y = by - 1;
         }
         else if (i == 1)
         {
            to_x = bx + 1, to_y = by;
         }
         else if (i == 2)
         {
            to_x = bx, to_y = by + 1;
         }
         else if (i == 3)
         {
            to_x = bx - 1, to_y = by;
         }
         if (to_x >= 0 && to_x < row && to_y >= 0 && to_y < col && maze[to_y][to_x] != '=' && !solution->contains(to_x, to_y))
         {
            bx = to_x, by = to_y;
            break;
         }
      }
      if (i == 4)
      {
         for (i = solution->size() - 1; i >= 0; i--)
         {
            Breadcrumb *now = solution->getPtr(i);
            // Mark b (current breadcrumb) as “stale”.
            if (now->getX() == bx && now->getY() == by)
            {
               now->setStale(true);
            }
            // Find the last good breadcrumb in the Trail T and go to this breadcrumb
            else if (now->isStale() == false)
            {
               bx = now->getX();
               by = now->getY();
               break;
            }
         }
      }
   }
}

Trail *MazeSolver::getSolution()
{
   return solution;
}
