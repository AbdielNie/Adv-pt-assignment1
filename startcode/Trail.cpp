
#include "Trail.h"

Trail::Trail()
{
   length = 0;
   // Dynamic Array Allocation
   breadcrumbs = new Breadcrumb *[TRAIL_ARRAY_MAX_SIZE];
}

Trail::~Trail()
{
   // free memory
   for (int i = 0; i < length; i++)
   {
      delete breadcrumbs[i];
   }
   delete[] breadcrumbs;
}

int Trail::size()
{
   return length;
}

Breadcrumb *Trail::getPtr(int i)
{
   return breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb *t)
{
   breadcrumbs[length++] = t;
}

bool Trail::contains(int x, int y)
{
   for (int i = 0; i < length; i++)
   {
      if (breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y)
      {
         return true;
      }
   }
   return false;
}
