#include "SimulatedAnnealing.h"
#include <iostream>
#include <queue>
#include <math.h>

SimulatedAnnealing::SimulatedAnnealing(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades)
: timetables(Timetables(_teachers, _classes, _grades)) {
    initialTemperature = 100.0;
    coolingRate = 0.99;
    numIterations = 10000;
}

Timetables SimulatedAnnealing::calculate() {
    Timetables current(timetables);

    double temperature = initialTemperature;
    queue<Swap> q;

    // for (int i = 0; i < numIterations; i++) timetables.makeRandomSwap();
    for (int i = 0; i < numIterations; i++) {
        int oldNumConflicts = current.getNumConflicts();

        Swap _swap = current.makeRandomSwap();

        int delta = current.getNumConflicts() - oldNumConflicts;

        if (delta <= 0 || (rand() / static_cast<double>(RAND_MAX)) < exp(-delta / temperature)) {
            q.push(_swap);
            if (current.getNumConflicts() < timetables.getNumConflicts()) {
                while (!q.empty()) {
                    timetables.makeSwap(q.front());
                    q.pop();
                }
            }
        } else {
            _swap.reverse();
            current.makeSwap(_swap);
        }

        temperature *= coolingRate;
    }

    return timetables;
}