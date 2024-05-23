#include "Class.h"
#include <algorithm>

Class::Class(string _id, string _gradeId, bool _hasDefaultSchedule)
    : id(_id), gradeId(_gradeId), hasDefaultSchedule(_hasDefaultSchedule), numAvailableTimes(0),
        availabilitySchedule(vector<vector<int>>(7)),
        defaultSchedule(vector<unordered_map<int, pair<string, string>>>(7)) {}

void Class::addTime(int time, string defaultSubject, string defaultTeacherId) {
    numAvailableTimes++;
    int minutesInDay = 24*60;
    
    int weekDay = time / minutesInDay;
    int timeInDay = time - (weekDay * minutesInDay);

    // sorted insert
    auto &v = availabilitySchedule[weekDay];
    v.insert(upper_bound(v.begin(), v.end(), timeInDay), timeInDay);
    
    if (hasDefaultSchedule) {
        auto &v = defaultSchedule[weekDay];
        defaultSchedule[weekDay][timeInDay] = {defaultSubject, defaultTeacherId};
    }
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

const vector<vector<int>> &Class::getAvailabilitySchedule() const {
    return availabilitySchedule;
}

const string Class::getId() const {
    return id;
}

const bool Class::getHasDefaultSchedule() const {
    return hasDefaultSchedule;
}

const pair<string,string> Class::getDefaultSchedule(int weekDay, int time) const {
    return defaultSchedule[weekDay].find(time)->second;
}

const string Class::getGradeId() const {
    return gradeId;
}