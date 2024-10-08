#include "Grade.h"

Grade::Grade() {}
Grade::Grade(string _id) : id(_id) {}

void Grade::addSubject(string subjectId, int numWeeklyLessons) {
    numWeeklyLessonsPerSubject[subjectId] = numWeeklyLessons;
    subjects.push_back({subjectId, numWeeklyLessons});
}

string Grade::toString() {
    string s = "Id da série: " + id + "\n";
    s += "Numero de disciplinas: " + to_string(numWeeklyLessonsPerSubject.size()) + "\n";
    for (auto subject : numWeeklyLessonsPerSubject) {
        s += subject.first + " (" + to_string(subject.second) + " aulas semanais)\n";
    }
    s += "\n";
    return s;
}

const string Grade::getId() const {
    return id;
}

int Grade::getNumWeeklyLessons(string subjectId) const {
    return numWeeklyLessonsPerSubject.find(subjectId)->second;
}

const vector<pair<string, int>> &Grade::getSubjects() const {
    return subjects;
}
