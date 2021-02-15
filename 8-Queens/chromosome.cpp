#include "chromosome.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Chromosome::Chromosome()
{
  state = makeState();
  fitnessScore = fitnessEval();
}

Chromosome::Chromosome(string newState)
{
  state = newState;
  fitnessScore = fitnessEval();
}

void Chromosome::print_state()
{
  cout << state << endl;
}

string Chromosome::makeState()
{
  string temp;
  int digit;
  srand(time(NULL));

  for(int i = 0; i < 8; ++i)
  {
    digit = rand() % 8+1;
    temp += to_string(digit);
  }

  return temp;
}

int Chromosome::fitnessEval()
{
  // maximum numbers of non-attacking pairs of queens (8*7/2)
  int fitness = 28; 
  string current;
  string next_queen;

  for(int i = 0; i < 8; ++i)
  {
    current = state[i];    
    int diagUp = stoi(current) + 1;
    int diagDown = stoi(current) - 1;
    for(int j = i+1; j < 8; ++j, ++diagUp, --diagDown)
    {
      next_queen = state[j];
      //Checks across
      if(state[i] == state[j])
        --fitness;
      //Checks diagonal up
      if(stoi(next_queen) == diagUp)
        --fitness;
      //Checks diagonal down
      if(stoi(next_queen) == diagDown)
        --fitness;
    }
  }

  return fitness;
}

