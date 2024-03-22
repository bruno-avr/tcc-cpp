#ifndef TIMETABLES_H
#define TIMETABLES_H
#include <vector>
#include <unordered_map>
#include "Teacher.h"
#include "Class.h"
#include "Grade.h"
#include "Timetable.h"

using namespace std;

class Timetables {
  int numClasses;
  vector<Class> classes;
  unordered_map<string, Grade> gradeById;
  unordered_map<string, string> teacherIdBySubjectId;
  vector<Timetable> timetables;
  int numConflicts;

public:
  Timetables(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades);
  string toString();

private:
  int calculateNumConflicts();

};


#endif