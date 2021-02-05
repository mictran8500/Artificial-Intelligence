//Michael Tran, CS441, Program 1
//Contains node structure for the 8 puzzle, as well as the Comparator for the priority queues
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node
{
  vector<vector<int>> state;
  int g;  //cost of path to get to node
  int h;  //heuristic function
  int f;  //evaluation function, g + h

  char move; //keeps track of which number the blank switched with

  node* parent;

  node()
  {
    g = 0;
    h = 0;
    f = 0;
    move = '0';
    parent = NULL;
  }

  node(vector<vector<int>> puzzle)
  {
    state = puzzle;
    g = 0;
    h = 0;
    f = 0;
    move = '0';
    parent = NULL;
  }

};

struct compare_astar
{
  bool operator()(const node* lhs, const node* rhs)
  {
    return lhs -> f > rhs -> f;
  }
};

struct compare_bfs
{
  bool operator()(const node* lhs, const node* rhs)
  {
    return lhs -> h > rhs -> h;
  }
};

extern vector<vector<int>> goal;
extern vector<node*> explored;
extern int ROW;
extern int COL;
