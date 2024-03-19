#include "Class.h"

Class::Class(string _id, string _gradeId)
    : id(_id), gradeId(_gradeId), numAvailableTimes(0), availabilitySchedule(vector<set<int>>(7)) {}

void Class::addTime(int time) {
    numAvailableTimes++;
    int minutesInDay = 24*60;
    
    int weekDay = time / minutesInDay;
    int timeInDay = time - (weekDay * minutesInDay);
    availabilitySchedule[weekDay].insert(timeInDay);
}

string Class::toString() {
    string s = "Id da turma: " + id + "\n";
    s += "Id da série correspondente: " + gradeId + "\n";
    s += "Horários disponíveis: (" + to_string(availabilitySchedule.size()) + ")";
    for (auto weekDay : availabilitySchedule) {
        for (auto time : weekDay) s += " " + to_string(time);
    }
    s += "\n\n";
    return s;
}