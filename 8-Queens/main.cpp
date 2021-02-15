#include "chromosome.h"
#include "population.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  
  Population initial;
  int solution = initial.solve();

  if(solution == 1)
    cout << "\nA solution to the 8-Queens problem has been found using a genetic algorithm. " << endl; 
  else
  {
    cout << "\nThe genetic algorithm ran for the max specified generations. " << endl;
    cout << "If the fitness score is not the max value, then you got bad rng. " << endl;
    cout << "Run the program again for hopefully better results. " << endl;
  }

  initial.topInPop();

  return 0;
}
