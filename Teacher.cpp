#include "Teacher.h"

Teacher::Teacher(string _id) : id(_id) {}

void Teacher::addSubject(string subject) {
    subjects.insert(subject);
}

string Teacher::toString() {
    string s = "Id do professor: " + id + "\n";
    s += "Numero de disciplinas: " + to_string(subjects.size()) + "\n";
    for (auto subject : subjects) {
        s += subject + "\n";
    }
    s += "\n";
    return s;
}