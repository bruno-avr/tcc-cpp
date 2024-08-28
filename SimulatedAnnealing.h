#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include "Teacher.h"
#include "Class.h"
#include "Grade.h"
#include "Timetables.h"

using namespace std;

class SimulatedAnnealing {
  Timetables timetables;
  double initialTemperature;
  double coolingRate;
  int numIterations;

public:
  SimulatedAnnealing(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades, unordered_map<string, unordered_set<int>> &_fixedTimes, bool useRandomDefaults=false);
  Timetables calculate();
private:
  void calculateSoft();
  void calculateHard();
};


#endif