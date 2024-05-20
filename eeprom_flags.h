#ifndef EEPROM_FLAGS_H
#define EEPROM_FLAGS_H

#include "EEPROM.h"

struct Motors_Flags {
  bool UNFINISHED_MOVEMENT_FLAG = 0; // 0 if every motor is in end position, 1 if some motors didn't finish their movement last time
  bool WALL_FLAG = 0; // 0 stands for closed, 1 for opened
  bool WALL_UNFINISHED_MOVEMENT_FLAG = 0;
  bool WALL_DISTANCE_IN_PARTS_FLAG[128]; // flags for passing through parts of the whole distance
  bool DOOR_FLAG = 0; // 0 stands for closed, 1 for opened
  bool DOOR_UNFINISHED_MOVEMENT_FLAG = 0;
  bool DOOR_DISTANCE_IN_PARTS_FLAG[128]; // flags for passing through parts of the whole distance
  bool TOP_FLAG = 1; // 0 stands for out of center, 1 for in center
  bool TOP_UNFINISHED_MOVEMENT_FLAG = 0;
  bool TOP_DISTANCE_IN_PARTS_FLAG[128]; // flags for passing through parts of the whole distance
  bool RIGHT_FLAG = 0; // 0 stands for out of center, 1 for in center
  bool RIGHT_UNFINISHED_MOVEMENT_FLAG = 0;
  bool RIGHT_DISTANCE_IN_PARTS_FLAG[128]; // flags for passing through parts of the whole distance
  bool BOTTOM_FLAG = 0; // 0 stands for out of center, 1 for in center
  bool BOTTOM_UNFINISHED_MOVEMENT_FLAG = 0;
  bool BOTTOM_DISTANCE_IN_PARTS_FLAG[128]; // flags for passing through parts of the whole distance
  bool LEFT_FLAG = 0; // 0 stands for out of center, 1 for in center
  bool LEFT_UNFINISHED_MOVEMENT_FLAG = 0;
  bool LEFT_DISTANCE_IN_PARTS_FLAG[128]; // flags for passing through parts of the whole distance
};

extern Motors_Flags motors_flags_to_get;
extern Motors_Flags motors_flags_to_put;

#endif /* EEPROM_FLAGS_H */