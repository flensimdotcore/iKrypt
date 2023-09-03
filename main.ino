#include <EEPROM.h>
#include <JC_Button.h>
#include "buttons.h"
#include "fsm.h"
#include "bluetooth.h"
#include "motors.h"
#include "rfid.h"

/* Defining LED strip pins */

#define LED_SIGNAL_PIN 2

/* Main functions */

void main_function() {
  if (INPUT_DATA_FLAG || BUTTON_FLAG) {
    FSM_classifier();
    INPUT_DATA_FLAG = 0;
    BUTTON_FLAG = 0;
  }
}

void test_function() {
  
}

void setup() {
  Serial.begin(9600); // For debugging via PC
  Serial1.begin(9600); // Bluetooth module
  Serial2.begin(9600); // RFID module

  FSM_table_init();

  buttons_init();

  stepper_init(WALL_DRIVE_STEP_PIN, WALL_DRIVE_DIR_PIN);
  stepper_init(DOOR_DRIVE_STEP_PIN, DOOR_DRIVE_DIR_PIN);
  stepper_init(LEFT_DRIVE_STEP_PIN, LEFT_DRIVE_DIR_PIN);
  stepper_init(RIGHT_DRIVE_STEP_PIN, RIGHT_DRIVE_DIR_PIN);
  stepper_init(TOP_DRIVE_STEP_PIN, TOP_DRIVE_DIR_PIN);
  stepper_init(BOTTOM_DRIVE_STEP_PIN, BOTTOM_DRIVE_DIR_PIN);
  stepper_init(CURTAIN1_DRIVE_STEP_PIN, CURTAIN1_DRIVE_DIR_PIN);
  stepper_init(CURTAIN2_DRIVE_STEP_PIN, CURTAIN2_DRIVE_DIR_PIN);

  cycles_left = EEPROM[10];
  TRIAL_PERIOD_FLAG = EEPROM[20];
  LICENSE_FLAG = EEPROM[30];
  WORK_FLAG = EEPROM[40];
}

void loop() {
  buttons_check();
  parser();

  if (TRIAL_PERIOD_FLAG && cycles_left < 1) {
    TRIAL_PERIOD_FLAG = 0;
    EEPROM.update(20, TRIAL_PERIOD_FLAG);
    TRIAL_PERIOD_FLAG = EEPROM[20];
  }

  if (TRIAL_PERIOD_FLAG || LICENSE_FLAG) {
    WORK_FLAG = 1;
    EEPROM.update(40, WORK_FLAG);
    WORK_FLAG = EEPROM[40];
  } else {
    WORK_FLAG = 0;
    EEPROM.update(40, WORK_FLAG);
    WORK_FLAG = EEPROM[40];
  }

  if (WORK_FLAG) {
    main_function();
  }
}
