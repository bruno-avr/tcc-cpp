#include "Teacher.h"

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

string Teacher::toString() {
    string s = "Id do professor: " + id + "\n";
    s += "Numero de disciplinas: " + to_string(subjects.size()) + "\n";
    for (auto subject : subjects) {
        s += subject.first + " " + subject.second + "\n";
    }
    s += "\n";
    return s;
}