#ifndef TEACHER_H
#define TEACHER_H
#include <string>
#include <set>

using namespace std;

class Teacher {
  string id;
  set<pair<string, string>> subjects;
  set<pair<int, int>> timeSlots;

public:
  Teacher(string _id);
  void addSubject(string subject, string classId);
  void addTimeSlot(int start, int end);
  string toString();
  const set<pair<string, string>> getSubjects() const;
  const string getId() const;

};


#endif