#include <iostream>
#include <string>
#include <vector>
#include "Teacher.h"
#include "Grade.h"
#include "Class.h"
#include "SimulatedAnnealing.h"
#include "Timetables.h"

using namespace std;

vector<Teacher> getTeachers() {
    int numTeachers, numSubjects;
    string teacherId, subjectId;
    vector<Teacher> teachers;

    cin >> numTeachers;

    for (int i = 0; i < numTeachers; i++) {
        cin >> teacherId >> numSubjects;
        Teacher teacher(teacherId);
        for (int j = 0; j < numSubjects; j++) {
            cin >> subjectId;
            teacher.addSubject(subjectId);
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

vector<Class> getClasses() {
    int numClasses, numTimes, time;
    string classId, gradeId;
    vector<Class> classes;

    cin >> numClasses;

    for (int i = 0; i < numClasses; i++) {
        cin >> classId >> gradeId >> numTimes;
        Class thisClass(classId, gradeId);
        for (int j = 0; j < numTimes; j++) {
            cin >> time;
            thisClass.addTime(time);
        }
        classes.push_back(thisClass);
    }

    return classes;
}

int main() {
    vector<Teacher> teachers = getTeachers();
    vector<Grade> grades = getGrades();
    vector<Class> classes = getClasses();

    SimulatedAnnealing simulatedAnnealing(teachers, grades, classes);
    Timetables schedule = simulatedAnnealing.calculate();
    
    // for (auto teacher : teachers) cout << teacher.toString();
    // for (auto grade : grades) cout << grade.toString();
    // for (auto thisClass : classes) cout << thisClass.toString();
    
    return 0;
}