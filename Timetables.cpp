#include "Timetables.h"
#include <iostream>
#include <stdlib.h>

Timetables::Timetables(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades) {
    for (auto &teacher : _teachers) {
        for (auto &subject : teacher.getSubjects()) {
            teacherIdBySubject[subject] = teacher.getId();
        }
    }

    classes = vector<Class>(_classes);
    for (auto grade : _grades) {
        gradeById[grade.getId()] = grade;
    }
    timetables = vector<Timetable>();

    for (int i = 0; i < _classes.size(); i++) {
        timetables.push_back(Timetable(_classes[i], gradeById[_classes[i].getGradeId()], teacherIdBySubject));
    }
    
    // calculating number of conflicts
    numConflicts = 0;
    for (int i = 0; i < timetables.size(); i++) {
        for (int j = i+1; j < timetables.size(); j++) {
            numConflicts += timetables[i].calculateNumConflicts(timetables[j]);
        }
        numConflicts += timetables[i].getNumOverloadedSubjects();
    }
}

int Timetables::getNumConflicts() {
    return numConflicts;
}

Swap Timetables::makeRandomSwap() {
    int randomTimetable = rand() % timetables.size();

    int oldNumConflicts = 0, newNumConflicts = 0;

    Swap swap = timetables[randomTimetable].getRandomSwap();
    swap.addTimetableIndex(randomTimetable);

    for (int i = 0; i < timetables.size(); i++) {
        if (i == randomTimetable) continue;
        oldNumConflicts+=timetables[randomTimetable].getNumConflictsInPos(timetables[i], swap.getDay1(), swap.getPos1());
        oldNumConflicts+=timetables[randomTimetable].getNumConflictsInPos(timetables[i], swap.getDay2(), swap.getPos2());
    }

    int delta = timetables[randomTimetable].makeSwap(swap);

    for (int i = 0; i < timetables.size(); i++) {
        if (i == randomTimetable) continue;
        newNumConflicts+=timetables[randomTimetable].getNumConflictsInPos(timetables[i], swap.getDay1(), swap.getPos1());
        newNumConflicts+=timetables[randomTimetable].getNumConflictsInPos(timetables[i], swap.getDay2(), swap.getPos2());
    }

    delta += newNumConflicts - oldNumConflicts;
    swap.addDelta(delta);
    
    numConflicts += delta;

    return swap;
}

void Timetables::makeSwap(Swap _swap) {
    timetables[_swap.getTimetableIndex()].makeSwap(_swap);
    numConflicts += _swap.getDelta();
}

string Timetables::toString() {
    string s = "";
    for (auto timetable : timetables) {
        s += timetable.toString() + "\n";
    }
    s += "\n";
    return s;
}

string Timetables::getJSON() {
    string s = "{\n";
    s += "  \"schedules\": [\n";
    for (int i = 0; i < timetables.size(); i++) {
        if (i > 0) s += ",\n";
        s += timetables[i].getJSON();
    }
    s += "\n  ]\n}";
    return s;
}