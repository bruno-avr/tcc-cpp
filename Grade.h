#ifndef GRADE_H
#define GRADE_H
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Grade {
  string id;
  unordered_map<string, int> numWeeklyLessonsPerSubject;
  vector<pair<string, int>> subjects;

public:
  Grade();
  Grade(string _id);
  
  void addSubject(string subjectId, int numWeeklyLessons);
  string toString();
  const string getId() const;
  int getNumWeeklyLessons(string subjectId) const;
  const vector<pair<string, int>> &getSubjects() const;

};


#endif