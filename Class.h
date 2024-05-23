#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;

class Class {
  string id, gradeId;
  int numAvailableTimes;
  bool hasDefaultSchedule;
  vector<vector<int>> availabilitySchedule;
  vector<unordered_map<int, pair<string, string>>> defaultSchedule;

public:
  Class(string _id, string _gradeId, bool _hasDefaultSchedule=false);
  void addTime(int time, string defaultSubject="", string defaultTeacherId="");
  string toString();
  const vector<vector<int>> &getAvailabilitySchedule() const;
  const string getId() const;
  const bool getHasDefaultSchedule() const;
  const pair<string, string> getDefaultSchedule(int weekDay, int time) const;
  const string getGradeId() const;

};


#endif