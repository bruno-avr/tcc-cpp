#include "Teacher.h"
const int CLASS_LENGTH = 50; // in minutes

Teacher::Teacher(string _id, int _priority) : id(_id), priority(_priority) {}

void Teacher::addSubject(string subject, string classId) {
    subjects.insert({subject, classId});
}

void Teacher::addTimeSlot(int start, int end) {
    timeSlots.insert({start, end});
}

const string Teacher::getId() const {
    return id;
}

const set<pair<string, string>> Teacher::getSubjects() const {
    return subjects;
}

bool Teacher::isAvailable(int start, int end) {
    auto it = timeSlots.lower_bound({start, start});

    if (it != timeSlots.end() && it->first <= start && end <= it->second) {
        return true;
    }

    if (it != timeSlots.begin()) {
        it--;
        if (it->first <= start && end <= it->second) {
            return true;
        }
    }

    return false;
}

int Teacher::getAvailabilityPenalty(int weekDay, int start) {
    int minutesInDay = 24*60;

    int newStart = weekDay*minutesInDay + start;
    int end = newStart + CLASS_LENGTH - 1;

    if (isAvailable(newStart, end)) return 0;
    
    return priority;
}

string Teacher::toString() {
    string s = "Id do professor: " + id + "\n";
    s += "Numero de disciplinas: " + to_string(subjects.size()) + "\n";
    for (auto subject : subjects) {
        s += subject.first + " " + subject.second + "\n";
    }
    s += "\n";
    return s;
}