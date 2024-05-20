#ifndef MOTORS_H
#define MOTORS_H

#include "fsm.h"
#include "buttons.h"
#include "bluetooth.h"
#include "rfid.h"
#include "GyverStepper.h"
#include "eeprom_flags.h"

/* Defines for stepper motors control parameters */

#define ACCELERATION 200
#define SPEED 2500 // Гене понравилось 1000, было 3000 рабочая

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

/* Defining distances for stepper motors */

#define WALL_DRIVE_DISTANCE 86450 // 5000 = 36 mm // СИЛОВАЯ СТВОРКА
#define DOOR_DRIVE_DISTANCE 5000 // ДЕКОРАТИВНАЯ ДВЕРКА
#define LEFT_DRIVE_DISTANCE 29000 // 57550 // НИЖНИЙ МОТОР // чуток переехал
#define RIGHT_DRIVE_DISTANCE 2300 // ЛЕВЫЙ МОТОР
#define TOP_DRIVE_DISTANCE 2300 // ПРАВЫЙ МОТОР
#define BOTTOM_DRIVE_DISTANCE 27700 // 55000 // ВЕРХНИЙ МОТОР // не доехал 1 см
#define CURTAIN1_DRIVE_DISTANCE 100
#define CURTAIN2_DRIVE_DISTANCE 100

typedef struct {
  uint8_t step_pin;
  uint8_t dir_pin;
  uint16_t distance;
} Drive;

extern Drive top_drive;
extern Drive right_drive;
extern Drive left_drive;
extern Drive bottom_drive;
extern Drive wall_drive;
extern Drive door_drive;

extern GStepper <STEPPER2WIRE> stepper;
extern GStepper <STEPPER2WIRE> right_drive_class;
extern GStepper <STEPPER2WIRE> left_drive_class;
extern GStepper <STEPPER2WIRE> top_drive_class;
extern GStepper <STEPPER2WIRE> bottom_drive_class;
extern GStepper <STEPPER2WIRE> door_drive_class;

void stepper_init(int _step, int _dir);
void open_wall();
void open_door();
void close_wall();
void close_door();
void motors_movement();
void finish_movement();

void move_right_drive_right();
void move_right_drive_left();
void move_left_drive_right();
void move_left_drive_left();
void move_top_drive_up();
void move_top_drive_down();
void move_bottom_drive_up();
void move_bottom_drive_down();

#endif /* MOTORS_H */
