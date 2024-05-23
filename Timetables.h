#ifndef TIMETABLES_H
#define TIMETABLES_H
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include "Teacher.h"
#include "Class.h"
#include "Grade.h"
#include "Timetable.h"
#include "Swap.h"

using namespace std;

class Timetables {
  int numClasses;
  vector<Class> classes;
  unordered_map<string, Grade> gradeById;
  map<pair<string, string>, string> teacherIdBySubject;
  vector<Timetable> timetables;
  int numConflicts;

public:
  Timetables(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades, unordered_map<string, unordered_set<int>> &_fixedTimes);
  string toString();
  string getJSON();
  int getNumConflicts();
  Swap makeRandomSwap();
  void makeSwap(Swap _swap);

};


#endif