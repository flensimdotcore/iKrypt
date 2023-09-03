#include "motors.h"

/* Structs containing pins and distances for each stepper motor */

Drive wall_drive = {
  WALL_DRIVE_STEP_PIN,
  WALL_DRIVE_DIR_PIN,
  WALL_DRIVE_DISTANCE
};

Drive door_drive = {
  DOOR_DRIVE_STEP_PIN,
  DOOR_DRIVE_DIR_PIN,
  DOOR_DRIVE_DISTANCE
};

Drive left_drive = {
  LEFT_DRIVE_STEP_PIN,
  LEFT_DRIVE_DIR_PIN,
  LEFT_DRIVE_DISTANCE
};

Drive right_drive = {
  RIGHT_DRIVE_STEP_PIN,
  RIGHT_DRIVE_DIR_PIN,
  RIGHT_DRIVE_DISTANCE
};

Drive top_drive = {
  TOP_DRIVE_STEP_PIN,
  TOP_DRIVE_DIR_PIN,
  TOP_DRIVE_DISTANCE
};

Drive bottom_drive = {
  BOTTOM_DRIVE_STEP_PIN,
  BOTTOM_DRIVE_DIR_PIN,
  BOTTOM_DRIVE_DISTANCE
};

Drive curtain1_drive = {
  CURTAIN1_DRIVE_STEP_PIN,
  CURTAIN1_DRIVE_DIR_PIN,
  CURTAIN1_DRIVE_DISTANCE
};

Drive curtain2_drive = {
  CURTAIN2_DRIVE_STEP_PIN,
  CURTAIN2_DRIVE_DIR_PIN,
  CURTAIN2_DRIVE_DISTANCE
};

/* Steppers functions */

void stepper_init(int _step, int _dir) {
  pinMode(_dir, OUTPUT);
  pinMode(_step, OUTPUT);
  delayMicroseconds(10);
}

void goOnDistanceInRevolutions(int _step, int _dir, unsigned long _distanceInRevolutions, bool _direction) {
  unsigned long _distance = 0;
  int _acceleration = ACCELERATION;
  delayMicroseconds(10);
  digitalWrite(_dir, _direction);
  delayMicroseconds(10);

  while(_distance <= _distanceInRevolutions) {
    _distance++;
    digitalWrite(_step, HIGH);
    delayMicroseconds(250 * _acceleration);
    digitalWrite(_step, LOW);
    delayMicroseconds(SPEED);
    if (_acceleration > 1) {
      _acceleration--;
    }
  }
  _distance = 0;
  _acceleration = ACCELERATION;
}

void open_wall() {
  goOnDistanceInRevolutions(WALL_DRIVE_STEP_PIN, WALL_DRIVE_DIR_PIN, WALL_DRIVE_DISTANCE, FORWARD);
}

void open_door() {
  goOnDistanceInRevolutions(DOOR_DRIVE_STEP_PIN, DOOR_DRIVE_DIR_PIN, DOOR_DRIVE_DISTANCE, FORWARD);
}

void close_wall() {
  goOnDistanceInRevolutions(WALL_DRIVE_STEP_PIN, WALL_DRIVE_DIR_PIN, WALL_DRIVE_DISTANCE, BACKWARDS);
}

void close_door() {
  goOnDistanceInRevolutions(DOOR_DRIVE_STEP_PIN, DOOR_DRIVE_DIR_PIN, DOOR_DRIVE_DISTANCE, BACKWARDS);
}

void move_to_center(Drive drive_struct) {
  goOnDistanceInRevolutions(drive_struct.step_pin, drive_struct.dir_pin, drive_struct.distance, FORWARD);
}

void move_out_of_center(Drive drive_struct) {
  goOnDistanceInRevolutions(drive_struct.step_pin, drive_struct.dir_pin, drive_struct.distance, BACKWARDS);
}

void motors_movement() {
  if (OPENED_FLAG) {
    switch (FSM_table[current_state][current_signal]) {
      case LEFT_CRATE_TO_RIGHT_CRATE_TRANSITION:
        move_out_of_center(left_drive);
        Serial.println("Left crate is out of center!");
        move_to_center(right_drive);
        Serial.println("Right crate is in center!");
        break;
      case LEFT_CRATE_TO_TOP_CRATE_TRANSITION:
        move_out_of_center(left_drive);
        Serial.println("Left crate is out of center!");
        move_to_center(top_drive);
        Serial.println("Top crate is in center!");
        break;
      case LEFT_CRATE_TO_BOTTOM_CRATE_TRANSITION:
        move_out_of_center(left_drive);
        Serial.println("Left crate is out of center!");
        move_to_center(bottom_drive);
        Serial.println("Bottom crate is in center!");
        break;
      case RIGHT_CRATE_TO_LEFT_CRATE_TRANSITION:
        move_out_of_center(right_drive);
        Serial.println("Right crate is out of center!");
        move_to_center(left_drive);
        Serial.println("Left crate is in center!");
        break;
      case RIGHT_CRATE_TO_TOP_CRATE_TRANSITION:
        move_out_of_center(right_drive);
        Serial.println("Right crate is out of center!");
        move_to_center(top_drive);
        Serial.println("Top crate is in center!");
        break;
      case RIGHT_CRATE_TO_BOTTOM_CRATE_TRANSITION:
        move_out_of_center(right_drive);
        Serial.println("Right crate is out of center!");
        move_to_center(bottom_drive);
        Serial.println("Bottom crate is in center!");
        break;
      case TOP_CRATE_TO_LEFT_CRATE_TRANSITION:
        move_out_of_center(top_drive);
        Serial.println("Top crate is out of center!");
        move_to_center(left_drive);
        Serial.println("Left crate is in center!");
        break;
      case TOP_CRATE_TO_RIGHT_CRATE_TRANSITION:
        move_out_of_center(top_drive);
        Serial.println("Top crate is out of center!");
        move_to_center(right_drive);
        Serial.println("Right crate is in center!");
        break;
      case TOP_CRATE_TO_BOTTOM_CRATE_TRANSITION:
        move_out_of_center(top_drive);
        Serial.println("Top crate is out of center!");
        move_to_center(bottom_drive);
        Serial.println("Bottom crate is in center!");
        break;
      case BOTTOM_CRATE_TO_LEFT_CRATE_TRANSITION:
        move_out_of_center(bottom_drive);
        Serial.println("Bottom crate is out of center!");
        move_to_center(left_drive);
        Serial.println("Left crate is in center!");
        break;
      case BOTTOM_CRATE_TO_RIGHT_CRATE_TRANSITION:
        move_out_of_center(bottom_drive);
        Serial.println("Bottom crate is out of center!");
        move_to_center(right_drive);
        Serial.println("Right crate is in center!");
        break;
      case BOTTOM_CRATE_TO_TOP_CRATE_TRANSITION:
        move_out_of_center(bottom_drive);
        Serial.println("Bottom crate is out of center!");
        move_to_center(top_drive);
        Serial.println("Top crate is in center!");
        break;
      case LEFT_CRATE_TO_CENTER_TRANSITION:
        move_to_center(left_drive);
        Serial.println("Left crate is in center!");
        break;
      case RIGHT_CRATE_TO_CENTER_TRANSITION:
        move_to_center(right_drive);
        Serial.println("Right crate is in center!");
        break;
      case TOP_CRATE_TO_CENTER_TRANSITION:
        move_to_center(top_drive);
        Serial.println("Top crate is in center!");
        break;
      case BOTTOM_CRATE_TO_CENTER_TRANSITION:
        move_to_center(bottom_drive);
        Serial.println("Bottom crate is in center!");
        break;
      case LEFT_CRATE_OUT_OF_CENTER_TRANSITION:
        move_out_of_center(left_drive);
        Serial.println("Left crate is out of center!");
        break;
      case RIGHT_CRATE_OUT_OF_CENTER_TRANSITION:
        move_out_of_center(right_drive);
        Serial.println("Right crate is out of center!");
        break;
      case TOP_CRATE_OUT_OF_CENTER_TRANSITION:
        move_out_of_center(top_drive);
        Serial.println("Top crate is out of center!");
        break;
      case BOTTOM_CRATE_OUT_OF_CENTER_TRANSITION:
        move_out_of_center(bottom_drive);
        Serial.println("Bottom crate is out of center!");
        break;
    }
  }
}