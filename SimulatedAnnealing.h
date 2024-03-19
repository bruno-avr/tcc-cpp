#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include <vector>
#include "Teacher.h"
#include "Grade.h"
#include "Class.h"
#include "Timetables.h"

using namespace std;

class SimulatedAnnealing {
  vector<Teacher> teachers;
  vector<Grade> grades;
  vector<Class> classes;

public:
  SimulatedAnnealing(vector<Teacher> _teachers, vector<Grade> _grades, vector<Class> _classes);
  
  Timetables calculate();
};


#endif