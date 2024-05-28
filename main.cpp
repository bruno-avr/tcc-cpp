#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>
#include "Teacher.h"
#include "Grade.h"
#include "Class.h"
#include "SimulatedAnnealing.h"
#include "Timetables.h"

using namespace std;

vector<Teacher> getTeachers() {
    int numTeachers, numSubjects;
    string teacherId, subjectId, classId;
    vector<Teacher> teachers;

    cin >> numTeachers;

    for (int i = 0; i < numTeachers; i++) {
        cin >> teacherId >> numSubjects;
        Teacher teacher(teacherId);
        for (int j = 0; j < numSubjects; j++) {
            cin >> subjectId >> classId;
            teacher.addSubject(subjectId, classId);
        }
        teachers.push_back(teacher);
    }

    return teachers;
}

vector<Grade> getGrades() {
    int numGrades, numSubjects, numLessons;
    string gradeId, subjectId;
    vector<Grade> grades;

    cin >> numGrades;

    for (int i = 0; i < numGrades; i++) {
        cin >> gradeId >> numSubjects;
        Grade grade(gradeId);
        for (int j = 0; j < numSubjects; j++) {
            cin >> subjectId >> numLessons;
            grade.addSubject(subjectId, numLessons);
        }
        grades.push_back(grade);
    }

    return grades;
}

unordered_map<string, unordered_set<int>> fixedTimes;

vector<Class> getClasses(string type) {
    bool hasDefaultSchedule = type == "calculate_score" or type == "fixed_recalculation";
    int numClasses, numTimes, time;
    string classId, gradeId, subjectId, teacherId;
    bool isFixed;
    vector<Class> classes;

    cin >> numClasses;

    for (int i = 0; i < numClasses; i++) {
        cin >> classId >> gradeId >> numTimes;
        Class thisClass(classId, gradeId, hasDefaultSchedule);
        for (int j = 0; j < numTimes; j++) {
            cin >> time;
            if (hasDefaultSchedule) {
                cin >> subjectId >> teacherId;
                thisClass.addTime(time, subjectId, teacherId);

                if (type == "fixed_recalculation") {
                    cin >> isFixed;
                    if (isFixed) fixedTimes[classId].insert(time);
                }
            } else {
                thisClass.addTime(time);
            }
        }
        classes.push_back(thisClass);
    }

    return classes;
}

int main() {
    srand(time(0));
    
    string type; cin >> type; // one of ["generate", "calculate_score", "fixed_recalculation"]
    if (type != "calculate_score") {
        string metaheuristic; cin >> metaheuristic; // one of ["simulatedAnnealing"]
    }

    vector<Teacher> teachers = getTeachers();
    vector<Grade> grades = getGrades();
    vector<Class> classes = getClasses(type);

    // for (auto teacher : teachers) cout << teacher.toString();
    // for (auto grade : grades) cout << grade.toString();
    // for (auto thisClass : classes) cout << thisClass.toString();

    if (type == "calculate_score") {
        Timetables timetables(teachers, classes, grades, fixedTimes);
        cout << timetables.getScoreJSON() << endl;
    } else {
        SimulatedAnnealing simulatedAnnealing(teachers, classes, grades, fixedTimes);
        Timetables timetables = simulatedAnnealing.calculate();
        cout << timetables.getJSON() << endl;
    }
    
    return 0;
}