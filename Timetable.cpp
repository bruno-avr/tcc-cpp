#include "Timetable.h"
#include <iostream>
#include <algorithm>
const string EMPTY = "EMPTY";
const int NUM_WEEK_DAYS = 7;
const int CLASS_LENGTH = 50; // in minutes
const int MAX_DAILY_CLASS_LIMIT = 2; // maximum number of the same class that can be held in a single day

Timetable::Timetable(Class &_class, Grade &_grade, map<pair<string,string>, string> &_teacherIdBySubject, unordered_set<int> &_fixedTimes) {
    classId = _class.getId();
    bool hasDefaultSchedule = _class.getHasDefaultSchedule();
    fixedTimes = _fixedTimes;
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

            if (hasDefaultSchedule) {
                auto &[subjectId, teacherId] = _class.getDefaultSchedule(weekDay, time);
                currSubjects[weekDay].push_back(subjectId);
                currTeachers[weekDay].push_back(teacherId);

            } else {
                if (currSubject == subjects.size()) { // if already disposed all subjects
                    currSubjects[weekDay].push_back(EMPTY);
                    currTeachers[weekDay].push_back(EMPTY);
                    continue;
                }

                currSubjects[weekDay].push_back(subjects[currSubject].first);
                // if class has a teacher for that subject
                if (_teacherIdBySubject.count({subjects[currSubject].first, classId})) {
                    currTeachers[weekDay].push_back(_teacherIdBySubject[{subjects[currSubject].first, classId}]);
                } else {
                    currTeachers[weekDay].push_back(EMPTY);
                }
            }

            if (currSubjects[weekDay].back() != EMPTY) {
                numSubjectsPerDay[weekDay][currSubjects[weekDay].back()]++;
            }

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

pair<int,int> Timetable::getValidDayPos() {
    bool validDay = false;
    int randomDay, randomPos;

    while (!validDay) {
        randomDay = getRandomDay();
        randomPos = rand() % startingTimes[randomDay].size();

        int thisTime = randomDay * 1440 + startingTimes[randomDay][randomPos];
        if (fixedTimes.count(thisTime) == 0) validDay = true;
    }

    return {randomDay, randomPos};
}

Swap Timetable::getRandomSwap() {
    auto [randomDay1, randomPos1] = getValidDayPos();
    auto [randomDay2, randomPos2] = getValidDayPos();

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

string Timetable::getJSON() {
    int minutesInDay = 24*60;
    string s = "    {\n";
    s += "      \"classId\": \"" + classId + "\",\n";
    s += "      \"lessons\": [\n";
    for (int i = 0; i < NUM_WEEK_DAYS; i++) {
        for (int j = 0; j < startingTimes[i].size(); j++) {
            if (i+j > 0) s += ",\n";
            s += "        {\n";
            int startingTime = startingTimes[i][j] + minutesInDay*i;
            if (fixedTimes.count(startingTime)) s += "          \"isSelected\": 1,\n";
            s += "          \"startingTime\": " + to_string(startingTime) + ",\n";
            s += "          \"subjectId\": \"" + currSubjects[i][j] + "\"\n";
            s += "        }";
        }
    }
    s += "\n      ]\n";
    s += "    }";
    return s;
}