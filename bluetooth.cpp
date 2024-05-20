#include "bluetooth.h"

char input_buffer[INPUT_BUFFER_SIZE];
int input_buffer_counter = 0;
bool INPUT_DATA_FLAG = 0;

bool TRIAL_PERIOD_FLAG = EEPROM[20];
bool LICENSE_FLAG = EEPROM[30];
bool WORK_FLAG = 1;

uint8_t cycles_left = EEPROM[10];

/* Bluetooth functions */

void license_activation() {
  int activation_input_buffer_counter = 0;
  char activation_input_buffer[INPUT_BUFFER_SIZE];

  for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
    activation_input_buffer[i] = input_buffer[i];
    Serial.print(input_buffer[i]);
  }

  if (activation_input_buffer == "AXZY-STPF-SRRE") {
    LICENSE_FLAG = 1;
    EEPROM.update(30, LICENSE_FLAG);
    LICENSE_FLAG = EEPROM[30];

    TRIAL_PERIOD_FLAG = 0;
    EEPROM.update(20, TRIAL_PERIOD_FLAG);
    TRIAL_PERIOD_FLAG = EEPROM[20];
    Serial1.write(ACTIVATION_SUCCESS);
  } else {
    Serial1.write(ACTIVATION_FAILURE);
  }
}

void ping_Bluetooth() {
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  
  while (Serial.available()) {
    Serial1.write(Serial.read());
  }
}

void parser() {
  input_buffer_counter = 0;

  while (Serial1.available() > 0) {
    if (input_buffer_counter <= INPUT_BUFFER_SIZE) {
      input_buffer[input_buffer_counter] = Serial1.read();
      input_buffer_counter++;
    }
    INPUT_DATA_FLAG = 1;
  }

  if (INPUT_DATA_FLAG) {
    if (input_buffer == PING) {
      ping_res();
    } else if (input_buffer_counter == 14) {
      switch (input_buffer[13]) {
        case 0:
          current_signal = LEFT_CRATE_SIGNAL;
          break;
        case 1:
          current_signal = BOTTOM_CRATE_SIGNAL;
          break;
        case 2:
          current_signal = TOP_CRATE_SIGNAL;
          break;
        case 3:
          current_signal = RIGHT_CRATE_SIGNAL;
          break;
      }
      switch_crate_res(STATUS_CODE_OK);
    } else if (input_buffer == GET_STATE) {
      get_state_res(STATUS_CODE_OK);
    } else if (input_buffer == CLOSE_DOOR) {
      current_signal = CLOSE_SIGNAL;
      close_door_res(STATUS_CODE_OK);
    }
    INPUT_DATA_FLAG = 0;
  } 
}


void ping() {
  Serial1.print("PING\t");
}

void ping_res() {
  Serial1.print("PING\t0x00\t");
}

void identify_res(char *STATUS_CODE) {
  Serial1.print("IDENTIFY\t");
  Serial1.print(STATUS_CODE);
  Serial1.print("\tIKRYPT 1.0,L:");
  if (LICENSE_FLAG) {
    Serial1.print("A:");
  } else {
    Serial1.print("T:");
  }
  Serial1.print(cycles_left, DEC);
  Serial1.print("\t");
}

void open_door_res(char *STATUS_CODE) {
  Serial1.print("OPEN_DOOR\t");
  Serial1.print(STATUS_CODE);
  Serial1.print("\t");
}

void switch_crate_res(char *STATUS_CODE) {
  Serial1.print("SWITCH_CRATE\t");
  Serial1.print(STATUS_CODE);
  Serial1.print("\t");
}

void get_state_res(char *STATUS_CODE) {
  Serial1.print("GET_STATE\t");
  Serial1.print(STATUS_CODE);
  Serial1.print("\t");
  Serial1.print(current_state);
  Serial1.print("\t");
}

void close_door_res(char *STATUS_CODE) {
  Serial1.print("CLOSE_DOOR\t");
  Serial1.print(STATUS_CODE);
  Serial1.print("\t");
}

