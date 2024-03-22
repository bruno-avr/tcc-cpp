#include "Timetable.h"
#include <iostream>
const string EMPTY = "EMPTY";
const int NUM_WEEK_DAYS = 7;
const int CLASS_LENGTH = 50; // in minutes

Timetable::Timetable(Class &_class, Grade &_grade, unordered_map<string, string> &_teacherIdBySubjectId) {
    classId = _class.getId();
    startingTimes = vector<vector<int>>(NUM_WEEK_DAYS);
    currSubjects = vector<vector<string>>(NUM_WEEK_DAYS);
    currTeachers = vector<vector<string>>(NUM_WEEK_DAYS);
    const vector<vector<int>> &availabilitySchedule = _class.getAvailabilitySchedule();
    const vector<pair<string, int>> &subjects = _grade.getSubjects();

    int currSubject = 0, numInserted = 0;
    for (int weekDay = 0; weekDay < availabilitySchedule.size(); weekDay++) {
        for (auto time : availabilitySchedule[weekDay]) {
            startingTimes[weekDay].push_back(time);

            if (currSubject == subjects.size()) { // if already disposed all subjects
                currSubjects[weekDay].push_back(EMPTY);
                currTeachers[weekDay].push_back(EMPTY);
                continue;
            }

            currSubjects[weekDay].push_back(subjects[currSubject].first);
            currTeachers[weekDay].push_back(_teacherIdBySubjectId[subjects[currSubject].first]);

            if (++numInserted == subjects[currSubject].second) { // if inserted all weekly classes of this subject
                numInserted = 0;
                currSubject++;
            }
        }
    }

    if (currSubject != subjects.size()) { // couldnt dispose all subjects
        cout << "Error: more subjects than available timespans." << endl;
    }
    
}

bool Timetable::isTeacherInTimestamp(string &teacherId, int weekDay, int startingTime) {
    // find some class that ends between the start and the end of this class
    auto low1 = lower_bound(startingTimes[weekDay].begin(), startingTimes[weekDay].end(), startingTime-CLASS_LENGTH+1);
    if (low1 != startingTimes[weekDay].end()) {
        int pos = low1 - startingTimes[weekDay].begin();
        if (startingTimes[weekDay][pos] < startingTime) {
            if (currTeachers[weekDay][pos] == teacherId) return true;
        }
    }

    // find some class that starts between the start and the end of this class
    auto low2 = lower_bound(startingTimes[weekDay].begin(), startingTimes[weekDay].end(), startingTime);
    if (low2 != startingTimes[weekDay].end()) {
        int pos = low2 - startingTimes[weekDay].begin();
        if (startingTimes[weekDay][pos] < startingTime+CLASS_LENGTH) {
            if (currTeachers[weekDay][pos] == teacherId) return true;
        }
    }
    return false;
}

int Timetable::calculateNumConflicts(Timetable &other) {
    int num = 0;
    for (int i = 0; i < NUM_WEEK_DAYS; i++) {
        for (int j = 0; j < currTeachers[i].size(); j++) {
            if (currTeachers[i][j] != EMPTY) {
                if (other.isTeacherInTimestamp(currTeachers[i][j], i, startingTimes[i][j])) {
                    num++;
                }
            }
        }
    }
    return num;
}

string convertTime(int time) {
    string hours = to_string(time / 60);
    if (hours.length() == 1) hours = "0" + hours;
    string minutes = to_string(time % 60);
    if (minutes.length() == 1) minutes = "0" + minutes;
    return hours + ":" + minutes;
}

string Timetable::toString() {
    string s = classId + "\n";
    string daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    for (int i = 0; i < NUM_WEEK_DAYS; i++) {
        s += daysOfWeek[i] + ": ";
        for (int j = 0; j < startingTimes[i].size(); j++) {
            s += "[" + convertTime(startingTimes[i][j]) + "] " + currSubjects[i][j] + " ; ";
        }
        s += "\n";
    }
    return s;
}