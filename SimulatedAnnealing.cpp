#include "SimulatedAnnealing.h"
#include <iostream>
#include <queue>
#include <math.h>

// Restrições soft:

// [DONE] As aulas de um professor são agendadas somente quando ele/ela está disponível.
// [DONE] Respeitar a prioridade de cada professor.
// [DONE] Uma turma não deve ter nenhum horário vago entre aulas.
// O tempo ocioso entre aulas de um professor deve ser o mínimo possível.
// remover esse: cada turma pode ter horários diferentes. se um professor quer um horário específico, pode adicionar conforme prioridade
// [DONE] Um professor não deve encontrar uma classe para mais de uma aula não consecutiva.
// [DONE] O número de dias que um professor é alocado deve ser o mínimo possível.

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

    // for (int i = 0; i < 100; i++) {
    for (int i = 0; i < numIterations; i++) {
        int oldNumConflicts = current.getNumConflicts();
        int oldPenalty = current.getPenalty();

        Swap _swap = current.makeRandomSwap();

        double delta = current.getPenalty() - oldPenalty;
        if (current.getNumConflicts() > oldNumConflicts) {
            // double temperatureFactor = ((100-temperature)/10.0)*((double)i/numIterations);
            // cout << "temperatureFactor: " << temperatureFactor << endl;
            // delta += (1.0+temperatureFactor) * (current.getNumConflicts() - oldNumConflicts);
            delta += current.getNumConflicts() - oldNumConflicts;
        }

        if (delta <= 0 || (rand() / static_cast<double>(RAND_MAX)) < exp(-delta / temperature)) {
            q.push(_swap);
            if (
                current.getNumConflicts() < timetables.getNumConflicts() or
                (
                    current.getNumConflicts() == timetables.getNumConflicts() and
                    current.getPenalty() < timetables.getPenalty()
                )
            ) {
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