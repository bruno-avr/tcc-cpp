#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include "Timetables.h"

using namespace std;

class SimulatedAnnealing {
  Timetables timetables;

public:
  SimulatedAnnealing(Timetables _timetables);
};


#endif