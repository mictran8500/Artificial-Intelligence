// Michael Tran
//
#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome.h"
#include <vector>

using namespace std;

class Population
{
  public:
    Population();
    ~Population();

    int generations;

    void print_population();
    int solve();
    int choose_parent();
    int breed(int p1, int p2);
    string mutatePct(string orginal);
    bool checkSolved();
    void topInPop();

  private:
    vector<Chromosome*> population;

};

#endif
