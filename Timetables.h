#ifndef TIMETABLES_H
#define TIMETABLES_H
#include <vector>
#include <unordered_map>
#include "Class.h"
#include "Grade.h"
#include "Timetable.h"

using namespace std;

class Timetables {
  int numClasses;
  vector<Class> classes;
  unordered_map<string, Grade> gradeById;
  vector<Timetable> timetables;

public:
  Timetables(vector<Class> &_classes, vector<Grade> &_grades);

};


#endif