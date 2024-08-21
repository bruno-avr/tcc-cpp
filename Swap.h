#ifndef SWAP_H
#define SWAP_H

using namespace std;

class Swap {
  int day1, pos1, day2, pos2, timetableIndex, delta, penaltyDelta;

public:
  Swap(int _day1, int _pos1, int _day2, int _pos2);
  void addTimetableIndex(int index);
  void addDelta(int _delta);
  void addPenaltyDelta(int _delta);
  int getDay1();
  int getPos1();
  int getDay2();
  int getPos2();
  int getTimetableIndex();
  int getDelta();
  int getPenaltyDelta();
  void reverse();

};


#endif