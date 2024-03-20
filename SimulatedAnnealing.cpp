#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(vector<Teacher> _teachers, vector<Grade> _grades, vector<Class> _classes)
    : teachers(_teachers), grades(_grades), classes(_classes) {}

Timetables SimulatedAnnealing::calculate() {
    Timetables schedule(classes, grades);
    return schedule;
}