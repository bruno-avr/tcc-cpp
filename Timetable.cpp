#include "Timetable.h"
#include <iostream>
#include <algorithm>
const string EMPTY = "EMPTY";
const int NUM_WEEK_DAYS = 7;
const int CLASS_LENGTH = 50; // in minutes
const int MAX_DAILY_CLASS_LIMIT = 2; // maximum number of the same class that can be held in a single day

Timetable::Timetable(Class &_class, Grade &_grade, unordered_map<string, string> &_teacherIdBySubjectId) {
    classId = _class.getId();
    startingTimes = vector<vector<int>>(NUM_WEEK_DAYS);
    currSubjects = vector<vector<string>>(NUM_WEEK_DAYS);
    currTeachers = vector<vector<string>>(NUM_WEEK_DAYS);
    numSubjectsPerDay = vector<unordered_map<string, int>>(NUM_WEEK_DAYS);
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
            numSubjectsPerDay[weekDay][subjects[currSubject].first]++;

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

int Timetable::getNumConflictsInTimestamp(string &teacherId, int weekDay, int startingTime) {
    int conflictsInTimestamp = 0;
    // find some class that ends between the start and the end of this class
    auto low1 = lower_bound(startingTimes[weekDay].begin(), startingTimes[weekDay].end(), startingTime-CLASS_LENGTH+1);
    if (low1 != startingTimes[weekDay].end()) {
        int pos = low1 - startingTimes[weekDay].begin();
        if (startingTimes[weekDay][pos] < startingTime) {
            if (currTeachers[weekDay][pos] == teacherId) conflictsInTimestamp++;
        }
    }

    // find some class that starts between the start and the end of this class
    auto low2 = lower_bound(startingTimes[weekDay].begin(), startingTimes[weekDay].end(), startingTime);
    if (low2 != startingTimes[weekDay].end()) {
        int pos = low2 - startingTimes[weekDay].begin();
        if (startingTimes[weekDay][pos] < startingTime+CLASS_LENGTH) {
            if (currTeachers[weekDay][pos] == teacherId) conflictsInTimestamp++;
        }
    }
    return conflictsInTimestamp;
}

int Timetable::calculateNumConflicts(Timetable &other) {
    int num = 0;
    for (int i = 0; i < NUM_WEEK_DAYS; i++) {
        for (int j = 0; j < currTeachers[i].size(); j++) {
            if (currTeachers[i][j] != EMPTY) {
                num += other.getNumConflictsInTimestamp(currTeachers[i][j], i, startingTimes[i][j]);
            }
        }
    }
    return num;
}

int Timetable::getNumConflictsInPos(Timetable &other, int weekDay, int pos) {
    if (currTeachers[weekDay][pos] != EMPTY) {
        return other.getNumConflictsInTimestamp(currTeachers[weekDay][pos], weekDay, startingTimes[weekDay][pos]);
    }
    return 0;
}

int Timetable::getNumOverloadedSubjects() {
    int num = 0;
    for (auto weekDay : numSubjectsPerDay) {
        for (auto subject : weekDay) {
            num += max(MAX_DAILY_CLASS_LIMIT, subject.second)-MAX_DAILY_CLASS_LIMIT;
        }
    }
    return num;
}

int Timetable::getRandomDay() {
    int randomDay;
    do { // it is expected that every timetable contains a non empty day
        randomDay = rand() % startingTimes.size();
    } while (startingTimes[randomDay].size() == 0);
    return randomDay;
}

Swap Timetable::getRandomSwap() {
    int randomDay1 = getRandomDay();
    int randomPos1 = rand() % startingTimes[randomDay1].size();

    int randomDay2 = getRandomDay();
    int randomPos2 = rand() % startingTimes[randomDay2].size();

    return Swap(randomDay1, randomPos1, randomDay2, randomPos2);
}

int Timetable::makeSwap(Swap &_swap) {
    int delta = 0;
    int oldSub = numSubjectsPerDay[_swap.getDay1()][currSubjects[_swap.getDay1()][_swap.getPos1()]]--;
    int oldAdd = numSubjectsPerDay[_swap.getDay1()][currSubjects[_swap.getDay2()][_swap.getPos2()]]++;
    if (oldSub > MAX_DAILY_CLASS_LIMIT) delta--;
    if (oldAdd >= MAX_DAILY_CLASS_LIMIT) delta++;

    oldSub = numSubjectsPerDay[_swap.getDay2()][currSubjects[_swap.getDay2()][_swap.getPos2()]]--;
    oldAdd = numSubjectsPerDay[_swap.getDay2()][currSubjects[_swap.getDay1()][_swap.getPos1()]]++;
    if (oldSub > MAX_DAILY_CLASS_LIMIT) delta--;
    if (oldAdd >= MAX_DAILY_CLASS_LIMIT) delta++;

    swap(currSubjects[_swap.getDay1()][_swap.getPos1()], currSubjects[_swap.getDay2()][_swap.getPos2()]);
    swap(currTeachers[_swap.getDay1()][_swap.getPos1()], currTeachers[_swap.getDay2()][_swap.getPos2()]);

    return delta;
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