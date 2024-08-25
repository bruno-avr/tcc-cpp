#include "Timetables.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>

Timetables::Timetables(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades, unordered_map<string, unordered_set<int>> &_fixedTimes) {
    for (auto &teacher : _teachers) {
        teacherByTeacherId.emplace(teacher.getId(), teacher);
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
        timetables.push_back(Timetable(_classes[i], gradeById[_classes[i].getGradeId()], teacherByTeacherId, teacherIdBySubject, _fixedTimes[_classes[i].getId()]));
    }
    
    // calculating number of conflicts
    numConflicts = 0;
    penalty = 0;
    for (int i = 0; i < timetables.size(); i++) {
        for (int j = i+1; j < timetables.size(); j++) {
            numConflicts += timetables[i].calculateNumConflicts(timetables[j]);
        }
        penalty += timetables[i].getIdlePenalty();
        penalty += timetables[i].getTeacherAvailabilityPenalty();
        penalty += timetables[i].getEmptyPenalty();
        numConflicts += timetables[i].getNumOverloadedSubjects();
    }
}

int Timetables::getNumConflicts() {
    return numConflicts;
}

int Timetables::getPenalty() {
    return penalty;
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

    auto [delta, penaltyDelta] = timetables[randomTimetable].makeSwap(swap);

    for (int i = 0; i < timetables.size(); i++) {
        if (i == randomTimetable) continue;
        newNumConflicts+=timetables[randomTimetable].getNumConflictsInPos(timetables[i], swap.getDay1(), swap.getPos1());
        newNumConflicts+=timetables[randomTimetable].getNumConflictsInPos(timetables[i], swap.getDay2(), swap.getPos2());
    }

    delta += newNumConflicts - oldNumConflicts;
    swap.addDelta(delta);
    
    numConflicts += delta;

    swap.addPenaltyDelta(penaltyDelta);
    
    penalty += penaltyDelta;

    return swap;
}

void Timetables::makeSwap(Swap _swap) {
    timetables[_swap.getTimetableIndex()].makeSwap(_swap);
    numConflicts += _swap.getDelta();
    penalty += _swap.getPenaltyDelta();
}

string Timetables::getScore() {
    long double eps = 1e-8;
    int score = 1e3*exp(-1e-3 * penalty) + eps;
    return to_string(score);
}

string Timetables::toString() {
    string s = "";
    for (auto timetable : timetables) {
        s += timetable.toString() + "\n";
    }
    s += "\n";
    return s;
}

string Timetables::getJSON(bool hideSchedules) {
    string s = "{\n";

    s += "  \"isFeasible\": ";
    if (numConflicts == 0) s += "true,\n";
    else s += "false,\n";

    if (hideSchedules) {
        s += "  \"score\": " + getScore() + "\n}";
    } else {
        s += "  \"score\": " + getScore() + ",\n";

        s += "  \"schedules\": [\n";
        for (int i = 0; i < timetables.size(); i++) {
            if (i > 0) s += ",\n";
            s += timetables[i].getJSON();
        }
        s += "\n  ]\n}";
    }
    return s;
}

string Timetables::getScoreJSON() {
    string s = "{\n";

    s += "  \"isFeasible\": ";
    if (numConflicts == 0) s += "true,\n";
    else s += "false,\n";

    s += "  \"score\": " + getScore() + "\n";

    s += "}";
    return s;
}