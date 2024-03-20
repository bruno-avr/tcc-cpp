#include "Timetable.h"
#include <iostream>

Timetable::Timetable(Class &_class, Grade &_grade) {
    const int numWeekDays = 7;
    startingTimes = vector<vector<int>>(numWeekDays);
    currSubjects = vector<vector<string>>(numWeekDays);
    const vector<vector<int>> &availabilitySchedule = _class.getAvailabilitySchedule();
    const vector<pair<string, int>> &subjects = _grade.getSubjects();

    int currSubject = 0, numInserted = 0;
    for (int weekDay = 0; weekDay < availabilitySchedule.size(); weekDay++) {
        for (auto time : availabilitySchedule[weekDay]) {
            if (currSubject == subjects.size()) break; // if already disposed all subjects

            startingTimes[weekDay].push_back(time);
            currSubjects[weekDay].push_back(subjects[currSubject].first);

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