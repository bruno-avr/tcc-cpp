#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <set>
#include <vector>

using namespace std;

class Class {
  string id, gradeId;
  int numAvailableTimes;
  vector<vector<int>> availabilitySchedule;

public:
  Class(string _id, string _gradeId);
  void addTime(int time);
  string toString();
  const vector<vector<int>> &getAvailabilitySchedule() const;
  const string getId() const;
  const string getGradeId() const;

};


#endif