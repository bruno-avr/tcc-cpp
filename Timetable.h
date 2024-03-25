#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <vector>
#include <string>
#include "Class.h"
#include "Grade.h"
#include "Swap.h"

using namespace std;

class Timetable {
  vector<vector<int>> startingTimes;
  vector<vector<string>> currSubjects;
  vector<vector<string>> currTeachers;
  string classId;

public:
  Timetable(Class &_class, Grade &_grade, unordered_map<string, string> &_teacherIdBySubjectId);
  string toString();
  int calculateNumConflicts(Timetable &other);
  int getNumConflictsInPos(Timetable &other, int weekDay, int pos);
  int getNumConflictsInTimestamp(string &teacherId, int weekDay, int startingTime);
  Swap getRandomSwap();
  void makeSwap(Swap &_swap);

private:
  int getRandomDay();

};


#endif