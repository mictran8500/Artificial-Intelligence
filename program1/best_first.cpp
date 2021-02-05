//Michael Tran, CS441, Program 1
//This file contains all functions regarding best-first search
#include <iostream>
#include <stdlib.h>
#include "8puzzle.h"

priority_queue<node*, vector<node*>, compare_bfs> frontier_b;

int heuristic_misplaced(node* current);
int heuristic_manhattan(node* current);
int min_heuristic(node* current);
void print_puzzle(node* current);
int goal_check(node* current);
int check_explored(vector<vector<int>> new_state);
void create_goal_path(node* current);
int check_solvable(node* current);

//  Creates child node, calculates h
int create_child_bfs(node* parent1, int init_row, int init_col, int new_row, int new_col, int choice, int m)
{
  // creating new state and swapping values
  int temp = parent1->state[new_row][new_col];
  vector<vector<int>> new_state = parent1 -> state;
  new_state[new_row][new_col] = 0;
  new_state[init_row][init_col] = temp;

  // checks if new state has already been explored
  if(check_explored(new_state) == 0)
  {
    node* child = new node(new_state);

    int new_h;
    if(choice == 1)
      new_h = heuristic_misplaced(child);
    else if(choice == 2)
      new_h = heuristic_manhattan(child);
    else
      new_h = min_heuristic(child);
    child -> h = new_h;
    //child -> move = temp;
    child -> move = m;
    child -> parent = parent1;

    // push child onto priority queue
    frontier_b.push(child);
  }

  return 0;
}

//  Calculates g,h,f and finds next state for children
int expand_children_bfs(node* current, int choice)
{
  vector<vector<int>> children;
  int row, col;

  // finding position of blank
  for(int i = 0; i < ROW; ++i)
  {
    for(int j = 0; j < COL; ++j)
    {
      if(current -> state[i][j] == 0)
      {
        row = i;
        col = j;
        break;
      }
    }
  }

  // finding coords for possible children nodes
  if(row != 0)
    create_child_bfs(current, row, col, row-1, col, choice, 'U');
  if(row != ROW-1)
    create_child_bfs(current, row, col, row+1, col, choice, 'D');
  if(col != 0)
    create_child_bfs(current, row, col, row, col-1, choice, 'L');
  if(col != COL-1)
    create_child_bfs(current, row, col, row, col+1, choice, 'R');

  return 0;
}

// A* search    *may specify 1 or 2 to switch between the two heuristics*
int bestfs(node* root, int choice)
{ 
  print_puzzle(root);

  // base case, checks if puzzle is solvable
  if(check_solvable(root))
  {
    cout << "Goal state is unreachable." << endl;
    return 0;
  }

  int steps = 0;
  node* current;
  if(choice == 1)
    root -> h = heuristic_misplaced(root);
  else if(choice == 2)
    root -> h = heuristic_manhattan(root);
  else
    root -> h = min_heuristic(root);
  root -> f = root -> h;
  root -> parent = NULL;

  // Adding node with initial state to priority queue
  frontier_b.push(root);  

  while(!frontier_b.empty())
  {
    // setting current to least cost node on frontier
    // popping from frontier, and pushing onto explored list
    current = frontier_b.top();
    frontier_b.pop();
    explored.push_back(current);

    // find goal path once goal is reached
    if(goal_check(current))
    {
      create_goal_path(current);
      cout << "Number of iterations: " << steps << endl;

      //empty frontier priority queue
      while(!frontier_b.empty())
        frontier_b.pop();

      //empty explored vector
      explored.clear();

      return 0;
    }

    // expand top of frontier, adding children to priority queue if
    // their states have not already been checked
    expand_children_bfs(current, choice);
    ++steps;
  }

  return 0;
}

