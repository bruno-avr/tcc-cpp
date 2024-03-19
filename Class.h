#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <set>
#include <vector>

using namespace std;

class Class {
  string id, gradeId;
  int numAvailableTimes;
  vector<set<int>> availabilitySchedule;

public:
  Class(string _id, string _gradeId);
  void addTime(int time);
  string toString();

};


#endif