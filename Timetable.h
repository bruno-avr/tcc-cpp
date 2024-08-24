#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <vector>
#include <string>
#include <unordered_set>
#include <map>
#include <utility>
#include "Class.h"
#include "Grade.h"
#include "Teacher.h"
#include "Swap.h"

using namespace std;

class Timetable {
  vector<vector<int>> startingTimes;
  vector<vector<string>> currSubjects;
  vector<vector<string>> currTeachers;
  vector<unordered_map<string, int>> numSubjectsPerDay;
  unordered_map<string, Teacher> &teacherByTeacherId;
  unordered_set<int> fixedTimes;
  string classId;

public:
  Timetable(Class &_class, Grade &_grade, unordered_map<string, Teacher> &_teacherByTeacherId, map<pair<string,string>, string> &_teacherIdBySubject, unordered_set<int> &_fixedTimes);
  string toString();
  string getJSON();
  int calculateNumConflicts(Timetable &other);
  int getIdlePenalty();
  int getTeacherAvailabilityPenalty();
  int getNumConflictsInPos(Timetable &other, int weekDay, int pos);
  int getNumConflictsInTimestamp(string &teacherId, int weekDay, int startingTime);
  Swap getRandomSwap();
  pair<int,int> makeSwap(Swap &_swap);
  int getNumOverloadedSubjects();

private:
  int getRandomDay();
  pair<int,int> getValidDayPos();
  int getDayIdlePenalty(int day);

};


#endif