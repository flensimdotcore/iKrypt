#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "buttons.h"
#include "fsm.h"
#include "motors.h"
#include "rfid.h"
#include <EEPROM.h>

/* Serial1 pins are Bluetooth ones */

#define INPUT_BUFFER_SIZE 19
extern char input_buffer[INPUT_BUFFER_SIZE];
extern int input_buffer_counter;
extern bool INPUT_DATA_FLAG;

/* Commands from module to phone */

#define RFID_AUTH_OK "RFID_AUTH\t0x00\t"
#define RFID_AUTH_FAIL "RFID_AUTH\t0x01\t"
#define LOCAL_STATE_CHANGE_EMPTY "LOCAL_STATE_CHANGE\t0x00\t0\t"
#define LOCAL_STATE_CHANGE_MONEY "LOCAL_STATE_CHANGE\t0x00\t1\t"
#define LOCAL_STATE_CHANGE_JEWELRY "LOCAL_STATE_CHANGE\t0x00\t2\t"
#define LOCAL_STATE_CHANGE_WATCHES "LOCAL_STATE_CHANGE\t0x00\t3\t"
#define LOCAL_STATE_CHANGE_DOOR_CLOSED "LOCAL_STATE_CHANGE\t0x00\t4\t"

/* Commands from phone to module */

#define PING "PING"
#define IDENTIFY "IDENTIFY"
#define OPEN_DOOR "OPEN_DOOR"
#define SWITCH_CRATE "SWITCH_CRATE"
#define GET_STATE "GET_STATE"
#define CLOSE_DOOR "CLOSE_DOOR"

/* Status and error codes */

#define STATUS_CODE_OK "0x00"
#define STATUS_CODE_RFID_NOT_PASSED "0x01"
#define STATUS_CODE_CRATE_ALREADY_IN_CENTER "0x02"
#define STATUS_CODE_AUTH_CODE_NOT_VALID "0x03"
#define STATUS_CODE_TRIAL_ALREADY_ACTIVE "0x04"
#define STATUS_CODE_CANT_ACCESS_MODULE "0x05"

extern bool TRIAL_PERIOD_FLAG;
extern bool LICENSE_FLAG;
extern bool WORK_FLAG;

extern uint8_t cycles_left;

void ping();
void ping_res();
void identify_res(char *STATUS_CODE);
void open_door_res(char *STATUS_CODE);
void switch_crate_res(char *STATUS_CODE);
void get_state_res(char *STATUS_CODE);
void close_door_res(char *STATUS_CODE);

void license_activation();
void ping_Bluetooth();
void parser();

#endif /* BLUETOOTH_H */
