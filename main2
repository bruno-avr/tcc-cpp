#include "Timetable.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const double initial_temperature = 100.0;
const double cooling_rate = 0.99;
const int num_iterations = 10000;
const int NUM_CLASSES = 3;
const int NUM_WORKING_DAYS = 5;
const int NUM_PERIODS_PER_WD = 5;
const int NUM_PERIODS = NUM_WORKING_DAYS * NUM_PERIODS_PER_WD;

vector<string> subjects;

// map<string, int> getMap(vector<string> &v) {
//     map<string, int> finalMap;
//     for (int i = 0; i < v.size(); i++) {
//         finalMap[v[i]] = i;
//     }
//     return finalMap;
// }

// map<string, int> getTeacherMap() {
//     vector<string> teachers = {
//         "Alice",
//         "Bob",
//         "Charlie",
//         "David",
//         "Eva",
//         "Fury",
//         "Gabrielle"
//     };
//     return getMap(teachers);
// }

void getSubjects() {
    vector<string> _subjects = {
        "MAT",
        "PORT",
        "HIS1",
        "CIE1",
        "HIS2",
        "CIE2",
    };
    subjects = _subjects;
}

vector<vector<int>> getNumSubjectsPerClass() {
    const int NUM_SUBJECTS = 6;
    vector<vector<int>> numSubjectsPerClass(NUM_CLASSES, vector<int>(NUM_SUBJECTS, 0));

    numSubjectsPerClass[0][0] = 5;
    numSubjectsPerClass[0][1] = 4;
    numSubjectsPerClass[0][2] = 2;
    numSubjectsPerClass[0][3] = 2;

    numSubjectsPerClass[1][0] = 5;
    numSubjectsPerClass[1][1] = 4;
    numSubjectsPerClass[1][2] = 2;
    numSubjectsPerClass[1][3] = 2;
    
    numSubjectsPerClass[2][0] = 5;
    numSubjectsPerClass[2][1] = 4;
    numSubjectsPerClass[2][4] = 3;
    numSubjectsPerClass[2][5] = 3;
    
    // numSubjectsPerClass[3][0] = 5;
    // numSubjectsPerClass[3][1] = 4;
    // numSubjectsPerClass[3][4] = 2;
    // numSubjectsPerClass[3][5] = 2;
    
    // numSubjectsPerClass[4][0] = 5;
    // numSubjectsPerClass[4][1] = 4;
    // numSubjectsPerClass[4][4] = 2;
    // numSubjectsPerClass[4][5] = 2;

    return numSubjectsPerClass;
}

Timetable simulatedAnnealing() {
    Timetable current(NUM_CLASSES, NUM_PERIODS, NUM_WORKING_DAYS);
    vector<vector<int>> numSubjectsPerClass = getNumSubjectsPerClass();
    current.generateFirst(numSubjectsPerClass);
    current.print(subjects);
    Timetable best = current;
    
    double temperature = initial_temperature;
    
    for (int iter = 0; iter < num_iterations; iter++) {
        Timetable neighbor = current;
        neighbor.makeRandomChange();
        neighbor.calculateConstraintsViolated();

        int delta = neighbor.getConstrintsViolated() - current.getConstrintsViolated();

        if (delta <= 0 || (rand() / static_cast<double>(RAND_MAX)) < exp(-delta / temperature)) {
            current = neighbor;

            if (neighbor.getConstrintsViolated() < best.getConstrintsViolated()) {
                best = neighbor;
            }
        }

        temperature *= cooling_rate;
    }

    return best;
}

main() {
    srand(time(0));
    getSubjects();
    
    Timetable timetable = simulatedAnnealing();

    timetable.print(subjects);
    // timetable.printConstrintsViolated();
    cout << "Constraints violated: " << timetable.getConstrintsViolated() << endl;

    return 0;
}