//Michael Tran, CS441, Program 1
#include <iostream>
#include <vector>
#include <queue>
#include "8puzzle.h"

using namespace std;

int bestfs(node* root, int choice);
int a_star_search(node* root, int choice);

int main()
{
  vector<vector<int>> trial1 = { {2,1,4}, {0,5,3}, {8,7,6} };
  vector<vector<int>> trial2 = { {0,1,3}, {4,2,5}, {7,8,6} };
  vector<vector<int>> trial3 = { {3,1,4}, {0,6,8}, {7,2,5} };
  vector<vector<int>> trial4 = { {1,0,4}, {2,6,3}, {5,7,8} };
  vector<vector<int>> trial5 = { {2,1,5}, {4,6,3}, {0,8,7} };

  //These initial states are unreachable
  //switch these trials in to see unreachable states
  vector<vector<int>> trial6 = { {1,3,4}, {8,6,2}, {0,7,5} };
  vector<vector<int>> trial7 = { {2,6,7}, {8,5,3}, {0,4,1} }; 

  // best first search with 3 different heuristics
  for(int i = 1; i <= 3; ++i)
  {
    if(i == 1)
      cout << "\nCommencing best first search with heuristic 1 (number of misplaced tiles)..." << endl;
    else if(i == 2)
      cout << "\nCommencing best first search with heuristic 2 (manhattan distance)..." << endl;
    else
      cout << "\nCommencing best first search with heuristic 3..." << endl;

    cout << "\n       [Trial 1]" << endl;
    node* puzzle = new node(trial1);
    bestfs(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 2]" << endl;
    puzzle = new node(trial2);
    bestfs(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 3]" << endl;
    puzzle = new node(trial3);
    bestfs(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 4]" << endl;
    puzzle = new node(trial4);
    bestfs(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 6]" << endl;
    puzzle = new node(trial6);
    bestfs(puzzle, i);
    delete puzzle;
  }

  // A* search with 3 different heuristics
  for(int i = 1; i <= 3; ++i)
  {
    if(i == 1)
      cout << "\nCommencing A* search with heuristic 1 (number of misplaced tiles)..." << endl;
    else if(i == 2)
      cout << "\nCommencing A* search with heuristic 2 (manhattan distance)..." << endl;
    else
      cout << "\nCommencing A* search with heuristic 3..." << endl;

    cout << "\n       [Trial 1]" << endl;
    node* puzzle = new node(trial1);
    a_star_search(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 2]" << endl;
    puzzle = new node(trial2);
    a_star_search(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 3]" << endl;
    puzzle = new node(trial3);
    a_star_search(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 4]" << endl;
    puzzle = new node(trial4);
    a_star_search(puzzle, i);
    delete puzzle;
    cout << "\n       [Trial 6]" << endl;
    puzzle = new node(trial6);
    a_star_search(puzzle, i);
    delete puzzle; 
  }

  return 0;
}
