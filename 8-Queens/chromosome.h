#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <string>

using namespace std;

class Chromosome
{
  public:
    string state;
    int fitnessScore;

    Chromosome();
    Chromosome(string newState);
    string makeState();
    int fitnessEval();
    void print_state();

};

#endif
