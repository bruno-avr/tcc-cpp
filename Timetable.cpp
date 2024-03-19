#include "Timetable.h"

Timetable::Timetable(Class &_class, Grade &_grade) {
    const int numWeekDays = 7;
    startingTimes = vector<vector<int>>(numWeekDays);
    currSubjects = vector<vector<int>>(numWeekDays);
    const vector<vector<int>> &availabilitySchedule = _class.getAvailabilitySchedule();
    // for (int i = 0; i < _class.; i++) {
    //     currSubjects
    //     availabilitySchedule[i]
    // }
    // _class.getAvailabilitySchedule();
}