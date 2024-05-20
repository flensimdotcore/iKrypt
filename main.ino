#include <EEPROM.h>
#include <JC_Button.h>
#include "buttons.h"
#include "fsm.h"
#include "bluetooth.h"
#include "motors.h"
#include "rfid.h"
#include "eeprom_flags.h"

bool TEST_INPUT_FLAG = 0;

String input_ble_buffer;

void test_function() {
  char input_byte;

  RFID_parser();
  
  if (Serial1.available() > 0) {
    input_ble_buffer = Serial1.readString();
    TEST_INPUT_FLAG = 1;
  } 

  if (TEST_INPUT_FLAG) {
    if (input_ble_buffer == "IDENTIFY")
    {
      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      Serial1.print("IDENTIFY OK\t0x00\tIKRYPT 1.0,L:A\t");
    }
    else if (input_ble_buffer == "GET_STATE")
    {
      String ble_str = "GET_STATE OK\t0x00\ta\t";
      uint8_t ble_current_state;

      if (OPENED_FLAG == 0)
      {
        ble_current_state = BLE_CLOSE_STATE;
      }
      else
      {
        ble_current_state = current_state;
      }

      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      sprintf(ble_str.c_str(), "GET_STATE OK\t0x00\t%d\t", ble_current_state);
      Serial1.print(ble_str.c_str());
    }
    else if (input_ble_buffer == "OPEN_DOOR" && !OPENED_FLAG)
    {
      digitalWrite(RELAY_PIN, HIGH);

      delay(1000);
      
      open_wall();
      open_door();

      digitalWrite(LED_PIN, HIGH);

      OPENED_FLAG = 1;

      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      Serial1.print("OPEN_DOOR OK\t0x00\t");
    }
    else if (input_ble_buffer == "CLOSE_DOOR" && OPENED_FLAG)
    {
      close_door();
      close_wall();

      current_signal = TOP_CRATE_SIGNAL;
      motors_movement();

      OPENED_FLAG = 0;

      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);

      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      Serial1.print("CLOSE_DOOR OK\t0x00\t");
    }
    else if (input_ble_buffer == "SWITCH_CRATE 0" && OPENED_FLAG)
    {
      current_signal = TOP_CRATE_SIGNAL;
      motors_movement();

      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      Serial1.print("SWITCH_CRATE OK\t0x00\t");
    }
    else if (input_ble_buffer == "SWITCH_CRATE 1" && OPENED_FLAG)
    {
      current_signal = LEFT_CRATE_SIGNAL;
      motors_movement();

      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      Serial1.print("SWITCH_CRATE OK\t0x00\t");
    }
    else if (input_ble_buffer == "SWITCH_CRATE 2" && OPENED_FLAG)
    {
      current_signal = BOTTOM_CRATE_SIGNAL;
      motors_movement();

      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      Serial1.print("SWITCH_CRATE OK\t0x00\t");
    }
    else if (input_ble_buffer == "SWITCH_CRATE 3" && OPENED_FLAG)
    {
      current_signal = RIGHT_CRATE_SIGNAL;
      motors_movement();

      if (Serial1.availableForWrite() < 1)
      {
        Serial1.flush();
      }
      Serial1.print("SWITCH_CRATE OK\t0x00\t");
    }
    
    TEST_INPUT_FLAG = 0;
  }

  buttons_check();
}

void setup() {
  Serial.begin(9600); // For debugging via PC
  Serial1.begin(9600); // Bluetooth module

  Serial1.flush();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  
  digitalWrite(LED_PIN, LOW);
  delay(200);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);

  FSM_table_init();

  buttons_init();

  RFID_init();

  stepper_init(WALL_DRIVE_STEP_PIN, WALL_DRIVE_DIR_PIN);
  stepper_init(DOOR_DRIVE_STEP_PIN, DOOR_DRIVE_DIR_PIN);
  stepper_init(LEFT_DRIVE_STEP_PIN, LEFT_DRIVE_DIR_PIN);
  stepper_init(RIGHT_DRIVE_STEP_PIN, RIGHT_DRIVE_DIR_PIN);
  stepper_init(TOP_DRIVE_STEP_PIN, TOP_DRIVE_DIR_PIN);
  stepper_init(BOTTOM_DRIVE_STEP_PIN, BOTTOM_DRIVE_DIR_PIN);
  stepper_init(CURTAIN2_DRIVE_STEP_PIN, CURTAIN2_DRIVE_DIR_PIN);
}

void loop() {
  test_function();
}
