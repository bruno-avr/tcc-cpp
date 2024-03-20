#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <vector>
#include <string>
#include "Class.h"
#include "Grade.h"

using namespace std;

class Timetable {
  vector<vector<int>> startingTimes;
  vector<vector<string>> currSubjects;

public:
  Timetable(Class &_class, Grade &_grade);

};


#endif