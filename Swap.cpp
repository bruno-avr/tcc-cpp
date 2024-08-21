#include "Swap.h"
#include <algorithm>

Swap::Swap(int _day1, int _pos1, int _day2, int _pos2) : day1(_day1), pos1(_pos1), day2(_day2), pos2(_pos2), delta(0), penaltyDelta(0) {}

void Swap::addTimetableIndex(int index) {
    timetableIndex = index;
}

void Swap::addDelta(int _delta) {
    delta += _delta;
}

void Swap::addPenaltyDelta(int _delta) {
    penaltyDelta += _delta;
}

int Swap::getDay1() {
    return day1;
}

int Swap::getPos1() {
    return pos1;
}

int Swap::getDay2() {
    return day2;
}

int Swap::getPos2() {
    return pos2;
}

int Swap::getTimetableIndex() {
    return timetableIndex;
}

int Swap::getDelta() {
    return delta;
}

int Swap::getPenaltyDelta() {
    return penaltyDelta;
}

void Swap::reverse() {
    swap(day1, day2);
    swap(pos1, pos2);
    delta *= -1;
    penaltyDelta *= -1;
}