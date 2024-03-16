#include "Class.h"

Class::Class(string _id, string _gradeId) : id(_id), gradeId(_gradeId) {}

void Class::addTime(int time) {
    availabilitySchedule.insert(time);
}

string Class::toString() {
    string s = "Id da turma: " + id + "\n";
    s += "Id da série correspondente: " + gradeId + "\n";
    s += "Horários disponíveis: (" + to_string(availabilitySchedule.size()) + ")";
    for (auto time : availabilitySchedule) {
        s += " " + to_string(time);
    }
    s += "\n\n";
    return s;
}