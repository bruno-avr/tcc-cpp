#include "SimulatedAnnealing.h"
#include <iostream>
#include <queue>
#include <math.h>

// Restrições soft:

// As aulas de um professor são agendadas somente quando ele/ela está disponível.
// Respeitar a prioridade de cada professor.
// Uma turma não deve ter nenhum horário vago entre aulas.
// O tempo ocioso entre aulas de um professor deve ser o mínimo possível.
// Um professor não deve encontrar uma classe para mais de uma aula não consecutiva.
// O número de dias que um professor é alocado deve ser o mínimo possível.

SimulatedAnnealing::SimulatedAnnealing(vector<Teacher> &_teachers, vector<Class> &_classes, vector<Grade> &_grades, unordered_map<string, unordered_set<int>> &_fixedTimes)
: timetables(Timetables(_teachers, _classes, _grades, _fixedTimes)) {
    initialTemperature = 100.0;
    coolingRate = 0.99;
    numIterations = 10000;
}

void SimulatedAnnealing::calculateHard() {
    Timetables current(timetables);

    double temperature = initialTemperature;
    queue<Swap> q;

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
                if (timetables.getNumConflicts() == 0) return;
            }
        } else {
            _swap.reverse();
            current.makeSwap(_swap);
        }

        temperature *= coolingRate;
    }
}

void SimulatedAnnealing::calculateSoft() {
    Timetables current(timetables);

    double temperature = initialTemperature;
    queue<Swap> q;

    for (int i = 0; i < numIterations; i++) {
        int oldNumConflicts = current.getPenalty();

        Swap _swap = current.makeRandomSwap();

        int delta = current.getPenalty() - oldNumConflicts;

        if (current.getNumConflicts() == 0 && (delta <= 0 || (rand() / static_cast<double>(RAND_MAX)) < exp(-delta / temperature))) {
            q.push(_swap);
            if (current.getPenalty() < timetables.getPenalty()) {
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
}

Timetables SimulatedAnnealing::calculate() {
    calculateHard();
    if (timetables.getNumConflicts() == 0) calculateSoft();

    return timetables;
}