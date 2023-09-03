#ifndef MOTORS_H
#define MOTORS_H

#include "fsm.h"
#include "buttons.h"
#include "bluetooth.h"
#include "rfid.h"
#include <EEPROM.h>

/* Defines for stepper motors control parameters */

#define ACCELERATION 5
#define SPEED 10

#define FORWARD 1
#define BACKWARDS 0

/* Defining pins for stepper motors */

#define WALL_DRIVE_STEP_PIN 30
#define WALL_DRIVE_DIR_PIN 31

#define DOOR_DRIVE_STEP_PIN 32
#define DOOR_DRIVE_DIR_PIN 33

#define LEFT_DRIVE_STEP_PIN 34
#define LEFT_DRIVE_DIR_PIN 35

#define RIGHT_DRIVE_STEP_PIN 36
#define RIGHT_DRIVE_DIR_PIN 37

#define TOP_DRIVE_STEP_PIN 38
#define TOP_DRIVE_DIR_PIN 39

#define BOTTOM_DRIVE_STEP_PIN 40
#define BOTTOM_DRIVE_DIR_PIN 41

#define CURTAIN2_DRIVE_STEP_PIN 42
#define CURTAIN2_DRIVE_DIR_PIN 43

#define CURTAIN1_DRIVE_STEP_PIN 44
#define CURTAIN1_DRIVE_DIR_PIN 45

/* Defining distances for stepper motors */

#define WALL_DRIVE_DISTANCE 10000
#define DOOR_DRIVE_DISTANCE 10000
#define LEFT_DRIVE_DISTANCE 10000
#define RIGHT_DRIVE_DISTANCE 10000
#define TOP_DRIVE_DISTANCE 10000
#define BOTTOM_DRIVE_DISTANCE 10000
#define CURTAIN1_DRIVE_DISTANCE 10000
#define CURTAIN2_DRIVE_DISTANCE 10000

typedef struct {
  uint8_t step_pin;
  uint8_t dir_pin;
  uint16_t distance;
} Drive;

void stepper_init(int _step, int _dir);
void goOnDistanceInRevolutions(int _step, int _dir, unsigned long _distanceInRevolutions, bool _direction);
void open_wall();
void open_door();
void close_wall();
void close_door();
void move_to_center(Drive drive_struct);
void move_out_of_center(Drive drive_struct);
void motors_movement();

#endif /* MOTORS_H */