#ifndef TEACHER_H
#define TEACHER_H
#include <string>
#include <unordered_set>

using namespace std;

class Teacher {
  string id;
  unordered_set<string> subjects;

public:
  Teacher(string _id);
  void addSubject(string subject);
  string toString();

};


#endif