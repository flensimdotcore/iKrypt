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

  // while (Serial1.available()) {
  //   if (activation_input_buffer_counter <= INPUT_BUFFER_SIZE) {
  //     activation_input_buffer[activation_input_buffer_counter] = Serial1.read();
  //     activation_input_buffer_counter++;
  //   }
  // }

  if (activation_input_buffer == "AXZY-STPF-SRRE-VPLK") {
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

void ping() {
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

  if (INPUT_DATA_FLAG && !LICENSE_FLAG && input_buffer[0] == LICENSE_ACTIVATION) {
    license_activation();
    INPUT_DATA_FLAG = 0;
  }
}