#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <vector>
#include "Class.h"
#include "Grade.h"

using namespace std;

class Timetable {
  vector<vector<int>> startingTimes;
  vector<vector<int>> currSubjects;

public:
  Timetable(Class &_class, Grade &_grade);

};


#endif