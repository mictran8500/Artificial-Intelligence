
#include "population.h"
#include "chromosome.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int POP_SIZE = 100;
int GEN_SIZE = 1000;
int MAX_FITNESS = 28;

Population::Population()
{
  
  for(int i = 0; i < POP_SIZE; ++i)
  {
    Chromosome* temp = new Chromosome();
    population.push_back(temp);
  }
  generations = 0;
}

Population::~Population()
{
  population.clear();
  generations = 0;
}

bool compare(Chromosome* ch1, Chromosome* ch2)
{
  return ch1->fitnessScore > ch2->fitnessScore; 
}

void Population::print_population()
{
  int size = population.size();
  for(int i = 0; i < size; ++i)
  {
    Chromosome* temp = population[i];
    cout << "Chromosome state: ";
    temp -> print_state();
    cout << "Fitness score: " << population[i]->fitnessScore << endl;
  }
}

//returns the index of the parent that was chosen from the population
int Population::choose_parent()
{
  int total = 0;

  int size = population.size();
  //counting total fitness for all chromosomes
  for(int i = 0; i < size; ++i)
  {
    total += population[i]->fitnessScore;
  }
 
  //creating and filling an array that represents the percentage of each chromosome being chosen as parent
  //chromosomes have a higher percentage of being chosen based on fitness score
  int fitnessPct[total];
  int index = 0;
  for(int i = 0; i < size; ++i)
  {
    int temp = population[i]->fitnessScore;
    for(int j = 0; j < temp; ++j)
    {
      fitnessPct[index] = i;
      ++index;
    }
  }

  int randIndex = rand() % total;

  return fitnessPct[randIndex];
}

string Population::mutatePct(string original)
{
  string mutated = original;
  int randPct = rand() % 100;

  //mutation has a 33% chance of occuring
  if(randPct < 33)
  {
    int randInd = rand() % 8;
    int randNum = rand() % 8+1;
    string temp = to_string(randNum);
    mutated[randInd] = temp[0];
  }

  return mutated;
}

//breeds the parents and adds both children to the population
int Population::breed(int p1, int p2)
{
  string parent1 = population[p1]->state;
  string parent2 = population[p2]->state;
  string child1 = parent1;
  string child2 = parent2;

  //random cross section index, crossover commencing
  int cross = rand() % 6 + 1;
  for(int i = cross; i < 8; ++i)
  {
    child1[i] = parent2[i];
    child2[i] = parent1[i];
  }

  //children has the chance of one of their genes mutating
  child1 = mutatePct(child1);
  child2 = mutatePct(child2);

  //adding children to the population
  Chromosome* temp = new Chromosome(child1);
  population.push_back(temp);

  Chromosome* temp1 = new Chromosome(child2);
  population.push_back(temp1);

  return 0;
}

//will stop the algorithm once the top 25% of the population is a solved state
//with max fitness score
bool Population::checkSolved()
{
  int sum = 0;
  for(int i = 0; i < POP_SIZE; ++i)
  {
    int score = population[i]->fitnessScore;
    if(score == MAX_FITNESS)
      ++sum;
  }

  if(sum > (POP_SIZE/4)+1)
    return true;
  else
    return false;

}

void Population::topInPop()
{
  cout << "\nSolution state: " << population[0]->state << endl;
  cout << "Fitness score: " << population[0]->fitnessScore << ", out of a maximum of 28." << endl;
  cout << "Generation found in: " << generations << endl << endl;
}

int Population::solve()
{
  int parent1, parent2;
  int popSize;
  bool flag;

  int genCount = 1;
  do{

    //sorting population from highest to least fitness score
    sort(population.begin(), population.end(), compare);


    //Prints current generation
    //and prints each chromosome state and fitness score as the algorithm runs
/*
    cout << "Commencing generation: " << genCount << " ..." << endl;
    print_population();
*/
    //checks to see if the majority of the population is a solved state
    flag = checkSolved();

    //removing the bottom 50% of fitness scores from the population
    for(int i = 0; i < POP_SIZE/2; ++i)
    {
      population.pop_back();
    } 

    //choosing parents and breeding them until the population 
    //is back to its original size
    do{

      parent1 = choose_parent();
      parent2 = choose_parent();
      breed(parent1, parent2);
      popSize = population.size();

    }while(popSize < POP_SIZE);

    ++genCount;

  }while(genCount < GEN_SIZE && flag == false);

  generations = genCount;

  return flag;

}

