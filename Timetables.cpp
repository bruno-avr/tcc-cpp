#include "Timetables.h"
#include <iostream>

Timetables::Timetables(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades) {
    for (auto teacher : _teachers) {
        for (auto subject : teacher.getSubjects()) {
            teacherIdBySubjectId[subject] = teacher.getId();
        }
    }

    classes = vector<Class>(_classes);
    for (auto grade : _grades) {
        gradeById[grade.getId()] = grade;
    }
    timetables = vector<Timetable>();

    for (int i = 0; i < _classes.size(); i++) {
        timetables.push_back(Timetable(_classes[i], gradeById[_classes[i].getGradeId()], teacherIdBySubjectId));
    }
    
    numConflicts = this->calculateNumConflicts();
}

int Timetables::calculateNumConflicts() {
    int num = 0;
    for (int i = 0; i < timetables.size(); i++) {
        for (int j = i+1; j < timetables.size(); j++) {
            num += timetables[i].calculateNumConflicts(timetables[j]);
        }
    }
    cout << "Num conflicts: " << num << endl;
    return num;
}

string Timetables::toString() {
    string s = "";
    for (auto timetable : timetables) {
        s += timetable.toString() + "\n";
    }
    s += "\n";
    return s;
}