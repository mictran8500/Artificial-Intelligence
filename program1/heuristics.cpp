//Michael Tran, CS441, Program 1
//This files contains the 3 heursistics that were implemented (Hamming, Manhattan, mean(h1,h2)
#include "8puzzle.h"

using namespace std;

//  Heuristic - number of misplaced tiles
int heuristic_misplaced(node* current)
{
  int count = 0;
  for(int i = 0; i < ROW; ++i)
  {
    for(int j = 0; j < COL; ++j)
    {
      if(current -> state[i][j] != goal[i][j])
        ++count;
    }
  }

  return count;
}

//  Heuristic - number of squares from desired location for each tile
int heuristic_manhattan(node* current)
{ 
  int i, j, k, l;
  int dist = 0;
  int total = 0;
  int flag;
  for(i = 0; i < ROW; ++i)
  {
    for(j = 0; j < COL; ++j)
    {
      if(current -> state[i][j] != goal[i][j])
      {
        int temp = current -> state[i][j];
        for(k = 0; k < ROW; ++k)
        {
          for(l = 0; l < COL; ++l)
          {
            if(temp == goal[k][l])
            {
              flag = 1;
              break;
            }
          }
          if(flag == 1)
            break;
        }

        dist = abs(i-k) + abs(j-l);
        total += dist;
      }
    }
  }

  return total;
}

// This heuristic combines both of the previous heuristics by the rule mean(h1, h2)
int min_heuristic(node* current)
{
  int m, n;
  m = heuristic_misplaced(current);
  n = heuristic_manhattan(current);

  int avg = (m+n)/2;

  return avg;
}
