//Michael Tran, CS441, Program 1
//This file contains functions regarding a_star search
#include <iostream>
#include <stdlib.h>
#include "8puzzle.h"

vector<vector<int>> goal = { {1,2,3}, {4,5,6}, {7,8,0} };
priority_queue<node*, vector<node*>, compare_astar> frontier;
vector<node*> explored;
int ROW = 3;
int COL = 3;

int heuristic_misplaced(node* current);
int heuristic_manhattan(node* current);
int min_heuristic(node* current);

//  Prints puzzle state
void print_puzzle(node* current)
{
  cout << "Initial state: (";
  for(int i = 0; i < ROW; ++i)
  {
    for(int j = 0; j < COL; ++j)
    {
      if(current->state[i][j] == 0)
        cout << "b";
      else
        cout << current->state[i][j];
    }
  }
  cout << ")" << endl;
}

//  Checks if goal is reached
int goal_check(node* current)
{
  if(current->h == 0)
    return 1;
  else
    return 0;
}

//  Checks if frontier state has already been explored
int check_explored(vector<vector<int>> new_state)
{
  int size = explored.size();
  int j, k, count;

  for(int i = 0; i < size; ++i)
  {
    count = 0;
    for(j = 0; j < ROW; ++j)
    {
      for(k = 0; k < COL; ++k)
      {
        if(new_state[j][k] == explored[i]->state[j][k])
          ++count;
      }
    }
    if(count == 9)
      return 1;
  }
  return 0;
}

//  Prints path from root to goal node (stores node* in vector)
void create_goal_path(node* current)
{
  int size;
  vector<node*> goal_path;
  node* temp = current;

  while(temp != NULL)
  {
    goal_path.push_back(temp);
    temp = temp -> parent;
  }

  size = goal_path.size();
  cout << "Number of steps: " << size-1 << endl;

  // printing out movements of blank
  cout << "Path: Blank-> " << endl;
  for(int i = size-2; i >= 0; --i)
    cout << goal_path[i] -> move;
  cout << endl;

  return;
}

//  Creates child node, calculates f, g, h, and new state
int create_child_astar(node* parent1, int init_row, int init_col, int new_row, int new_col, int choice, int m)
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

    int new_g = parent1->g + 1;
    int new_h;
    if(choice == 1)
      new_h = heuristic_misplaced(child);
    else if(choice == 2)
      new_h = heuristic_manhattan(child);
    else
      new_h = min_heuristic(child);
    int new_f = new_g + new_h;

    // insert values into new child
    child -> g = new_g;
    child -> h = new_h;
    child -> f = new_f;
    //child -> move = temp;
    child -> move = m;
    child -> parent = parent1;

    // push child onto priority queue
    frontier.push(child);
  }

  return 0;
}

//  Calculates g,h,f and finds next state for children
int expand_children_astar(node* current, int choice)
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
    create_child_astar(current, row, col, row-1, col, choice, 'U');
  if(row != ROW-1)
    create_child_astar(current, row, col, row+1, col, choice, 'D');
  if(col != 0)
    create_child_astar(current, row, col, row, col-1, choice, 'L');
  if(col != COL-1)
    create_child_astar(current, row, col, row, col+1, choice, 'R');

  return 0;
}

// Checks if the puzzle if solvable using inversion values
int check_solvable(node* current)
{
  int count = 0;
  vector<int> state;
  vector<int> temp;

  for(int i = 0; i < ROW; ++i)
  {
    for(int j = 0; j < COL; ++j)
    {
      temp.push_back(current->state[i][j]);
    }
  }
  state = temp;
  int size = temp.size();

  for(int i = 0; i < size; ++i)
  {
    if(state[i] != 0)
    {
      for(int j = i; j < size; ++j)
      {
        if(temp[j] < state[i] && temp[j] != 0)
          ++count;
      }
    }
  }
  return count%2;
}

// A* search
int a_star_search(node* root, int choice)
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
  frontier.push(root);  

  while(!frontier.empty())
  {
    // setting current to least cost node on top frontier
    // popping from frontier, and pushing onto explored list
    current = frontier.top();
    frontier.pop();
    explored.push_back(current);

    // find goal path once goal is reached
    if(goal_check(current))
    {
      create_goal_path(current);
      cout << "Number of iterations: " << steps << endl;

      //empty frontier priority queue
      while(!frontier.empty())
        frontier.pop();

      //empty explored vector
      explored.clear();

      return 0;
    }

    // expand top of frontier, adding children to priority queue if
    // their states have not already been checked
    expand_children_astar(current, choice);
    ++steps;
  }

  return 0;
}

