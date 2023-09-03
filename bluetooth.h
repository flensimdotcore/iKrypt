#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "buttons.h"
#include "fsm.h"
#include "motors.h"
#include "rfid.h"
#include <EEPROM.h>


/* Defining Bluetooth module pins and more */

/* Serial1 pins are Bluetooth ones */

#define INPUT_BUFFER_SIZE 19
extern char input_buffer[INPUT_BUFFER_SIZE];
extern int input_buffer_counter;
extern bool INPUT_DATA_FLAG;

#define ACTIVATION_INPUT_BUFFER_SIZE 20
#define ACTIVATION_SUCCESS 'S' // SUCCESS
#define ACTIVATION_FAILURE 'F' // FAILURE

/* Defines for commands codes */

#define OPEN 'O' // OPEN
#define LEFT_CRATE 'L' // LEFT
#define RIGHT_CRATE 'R' // RIGHT
#define TOP_CRATE 'T' // TOP
#define BOTTOM_CRATE 'B' // BOTTOM
#define CLOSE 'C' // CLOSE
#define EMPTY_CENTER 'E' // EMPTY
#define LICENSE_ACTIVATION 'A' // ACTIVATION

/* Defines for timers */

#define BENCHMARK_TEST_TIME 3600000 // 1 hour in milliseconds

/* Special defines */

//#define DEBUG // All the functions as in RELEASE version except some values are shown in Serial monitor
//#define TEST // Benchmark test for studying a device's behaviour in extreme situations
//#define RELEASE // Final stable version of firmware for consumers

extern bool TRIAL_PERIOD_FLAG;
extern bool LICENSE_FLAG;
extern bool WORK_FLAG;

extern uint8_t cycles_left;

void license_activation();
void ping();
void parser();

#endif /* BLUETOOTH_H */