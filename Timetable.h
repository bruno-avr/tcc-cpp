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
  vector<vector<string>> currTeachers;
  string classId;

public:
  Timetable(Class &_class, Grade &_grade, unordered_map<string, string> &_teacherIdBySubjectId);
  string toString();
  int calculateNumConflicts(Timetable &other);
  bool isTeacherInTimestamp(string &teacherId, int weekDay, int startingTime);

};


#endif