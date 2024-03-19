#include "Timetables.h"

Timetables::Timetables(vector<Class> &_classes, vector<Grade> &_grades) {
    classes = vector<Class>(_classes);
    for (auto grade : _grades) {
        gradeById[grade.getId()] = grade;
    }
    timetables = vector<Timetable>();

    for (int i = 0; i < _classes.size(); i++) {
        timetables.push_back(Timetable(_classes[i], gradeById[_classes[i].getGradeId()]));
    }
}