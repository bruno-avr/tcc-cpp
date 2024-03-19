#ifndef GRADE_H
#define GRADE_H
#include <string>
#include <unordered_map>

using namespace std;

class Grade {
  string id;
  unordered_map<string, int> numWeeklyLessonsPerSubject;

public:
  Grade(string _id);
  
  void addSubject(string subjectId, int numWeeklyLessons);
  string toString();
  const string getId() const;

};


#endif