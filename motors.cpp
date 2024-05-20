#include "motors.h"

#define LED_PIN 20
#define RELAY_PIN 21

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

Drive curtain2_drive = {
  CURTAIN2_DRIVE_STEP_PIN,
  CURTAIN2_DRIVE_DIR_PIN,
  CURTAIN2_DRIVE_DISTANCE
};

GStepper <STEPPER2WIRE> stepper(400, WALL_DRIVE_STEP_PIN, WALL_DRIVE_DIR_PIN);
GStepper <STEPPER2WIRE> right_drive_class(400, RIGHT_DRIVE_STEP_PIN, RIGHT_DRIVE_DIR_PIN);
GStepper <STEPPER2WIRE> left_drive_class(400, LEFT_DRIVE_STEP_PIN, LEFT_DRIVE_DIR_PIN);
GStepper <STEPPER2WIRE> top_drive_class(400, TOP_DRIVE_STEP_PIN, TOP_DRIVE_DIR_PIN);
GStepper <STEPPER2WIRE> bottom_drive_class(400, BOTTOM_DRIVE_STEP_PIN, BOTTOM_DRIVE_DIR_PIN);
GStepper <STEPPER2WIRE> door_drive_class(400, DOOR_DRIVE_STEP_PIN, DOOR_DRIVE_DIR_PIN);

/* Steppers functions */

void stepper_init(int _step, int _dir) {
  stepper.setAcceleration(ACCELERATION); // ускорение
  stepper.setMaxSpeed(SPEED);     // скорость движения к цели
  stepper.setRunMode(FOLLOW_POS);

  right_drive_class.setAcceleration(ACCELERATION); // ускорение
  right_drive_class.setMaxSpeed(SPEED);     // скорость движения к цели
  right_drive_class.setRunMode(FOLLOW_POS);

  left_drive_class.setAcceleration(ACCELERATION); // ускорение
  left_drive_class.setMaxSpeed(SPEED);     // скорость движения к цели
  left_drive_class.setRunMode(FOLLOW_POS);

  top_drive_class.setAcceleration(ACCELERATION); // ускорение
  top_drive_class.setMaxSpeed(SPEED);     // скорость движения к цели
  top_drive_class.setRunMode(FOLLOW_POS);

  bottom_drive_class.setAcceleration(ACCELERATION); // ускорение
  bottom_drive_class.setMaxSpeed(SPEED - 200);     // скорость движения к цели
  bottom_drive_class.setRunMode(FOLLOW_POS);

  door_drive_class.setAcceleration(ACCELERATION); // ускорение
  door_drive_class.setMaxSpeed(SPEED);     // скорость движения к цели
  door_drive_class.setRunMode(FOLLOW_POS);

  delayMicroseconds(10);
}

void finish_movement() {
  if (motors_flags_to_get.BOTTOM_UNFINISHED_MOVEMENT_FLAG == 1) {
    if (motors_flags_to_get.BOTTOM_FLAG == 0) {
      move_bottom_drive_up();
    } else {
      move_bottom_drive_down();
    }
  } else if (motors_flags_to_get.RIGHT_UNFINISHED_MOVEMENT_FLAG == 1) {
    if (motors_flags_to_get.RIGHT_FLAG == 0) {
      move_right_drive_left();
    } else {
      move_right_drive_right();
    }
  } else if (motors_flags_to_get.TOP_UNFINISHED_MOVEMENT_FLAG == 1) {
    if (motors_flags_to_get.TOP_FLAG == 0) {
      move_top_drive_down();
    } else {
      move_top_drive_up();
    }
  } else if (motors_flags_to_get.LEFT_UNFINISHED_MOVEMENT_FLAG == 1) {
    if (motors_flags_to_get.LEFT_FLAG == 0) {
      move_left_drive_right();
    } else {
      move_left_drive_left();
    }
  } else if (motors_flags_to_get.DOOR_UNFINISHED_MOVEMENT_FLAG == 1) {
    if (motors_flags_to_get.DOOR_FLAG == 0) {
      close_door();
    } else {
      open_door();
    }
  } else if (motors_flags_to_get.WALL_UNFINISHED_MOVEMENT_FLAG == 1) {
    if (motors_flags_to_get.WALL_FLAG == 0) {
      close_wall();
    } else {
      open_wall();
    }
  }
}

void move_left_drive_left() { // LEFT
  Serial.println("Left crate moving out of center");
  motors_flags_to_put.LEFT_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!right_drive_class.tick()) {
      right_drive_class.setTarget(RIGHT_DRIVE_DISTANCE, RELATIVE);
      start_pos = right_drive_class.getCurrent();
    }

    if (right_drive_class.getCurrent() >= right_drive_class.getTarget()) {
      Serial.println("Left crate is out of center");
      motors_flags_to_put.LEFT_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.LEFT_FLAG = 0;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.LEFT_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void move_left_drive_right() { // LEFT
  Serial.println("Left crate moving in center");
  motors_flags_to_put.LEFT_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!right_drive_class.tick()) {
      right_drive_class.setTarget((0 - RIGHT_DRIVE_DISTANCE), RELATIVE);
      start_pos = right_drive_class.getCurrent();
    }

    if (right_drive_class.getCurrent() <= right_drive_class.getTarget()) {
      Serial.println("Left crate is in center");
      motors_flags_to_put.LEFT_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.LEFT_FLAG = 1;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.LEFT_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void move_bottom_drive_down() { // BOTTOM
  Serial.println("Bottom crate moving out of center");
  motors_flags_to_put.BOTTOM_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!left_drive_class.tick()) {
      left_drive_class.setTarget(LEFT_DRIVE_DISTANCE, RELATIVE);
      start_pos = left_drive_class.getCurrent();
    }

    if (left_drive_class.getCurrent() >= left_drive_class.getTarget()) {
      Serial.println("Bottom crate is out of center");
      motors_flags_to_put.BOTTOM_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.BOTTOM_FLAG = 0;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.BOTTOM_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void move_bottom_drive_up() { // BOTTOM
  Serial.println("Bottom crate moving in center");
  motors_flags_to_put.BOTTOM_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!left_drive_class.tick()) {
      left_drive_class.setTarget((0 - LEFT_DRIVE_DISTANCE), RELATIVE);
      start_pos = left_drive_class.getCurrent();
    }

    if (left_drive_class.getCurrent() <= left_drive_class.getTarget()) {
      Serial.println("Bottom crate is in center");
      motors_flags_to_put.BOTTOM_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.BOTTOM_FLAG = 1;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.BOTTOM_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void move_right_drive_left() { // RIGHT
  Serial.println("Right crate moving in center");
  motors_flags_to_put.RIGHT_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!top_drive_class.tick()) {
      top_drive_class.setTarget(TOP_DRIVE_DISTANCE, RELATIVE);
      start_pos = top_drive_class.getCurrent();
    }

    if (top_drive_class.getCurrent() >= top_drive_class.getTarget()) {
      Serial.println("Right crate is in center");
      motors_flags_to_put.RIGHT_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.RIGHT_FLAG = 1;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.RIGHT_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void move_top_drive_up() { // TOP
  Serial.println("Top crate moving out of center");
  motors_flags_to_put.TOP_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!bottom_drive_class.tick()) {
      bottom_drive_class.setTarget(BOTTOM_DRIVE_DISTANCE, RELATIVE);
      start_pos = bottom_drive_class.getCurrent();
    }

    if (bottom_drive_class.getCurrent() >= bottom_drive_class.getTarget()) {
      Serial.println("Top crate is out of center");
      motors_flags_to_put.TOP_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.TOP_FLAG = 0;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.TOP_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void move_right_drive_right() { // RIGHT
  Serial.println("Right crate moving out of center");
  motors_flags_to_put.RIGHT_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!top_drive_class.tick()) {
      top_drive_class.setTarget((0 - TOP_DRIVE_DISTANCE), RELATIVE);
      start_pos = top_drive_class.getCurrent();
    }

    if (top_drive_class.getCurrent() <= top_drive_class.getTarget()) {
      Serial.println("Right crate is out of center");
      motors_flags_to_put.RIGHT_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.RIGHT_FLAG = 0;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.RIGHT_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void move_top_drive_down() { // TOP
  Serial.println("Top crate moving in center");
  motors_flags_to_put.TOP_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!bottom_drive_class.tick()) {
      bottom_drive_class.setTarget((0 - BOTTOM_DRIVE_DISTANCE), RELATIVE);
      start_pos = top_drive_class.getCurrent();
    }

    if (bottom_drive_class.getCurrent() <= bottom_drive_class.getTarget()) {
      Serial.println("Top crate is in center");
      motors_flags_to_put.TOP_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.TOP_FLAG = 1;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.TOP_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void close_door() { // DOOR
  motors_flags_to_put.DOOR_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!stepper.tick()) {
      stepper.setTarget(WALL_DRIVE_DISTANCE, RELATIVE);
      start_pos = stepper.getCurrent();
    }

    if (stepper.getCurrent() >= stepper.getTarget()) {
      motors_flags_to_put.DOOR_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.DOOR_FLAG = 1;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.DOOR_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void close_wall() {
  motors_flags_to_put.WALL_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!door_drive_class.tick()) {
      door_drive_class.setTarget((0 - DOOR_DRIVE_DISTANCE), RELATIVE);
      start_pos = door_drive_class.getCurrent();
    }

    if (door_drive_class.getCurrent() <= door_drive_class.getTarget()) {
      motors_flags_to_put.WALL_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.WALL_FLAG = 1;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.WALL_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void open_door() { // DOOR
  motors_flags_to_put.DOOR_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!stepper.tick()) {
      stepper.setTarget((0 - WALL_DRIVE_DISTANCE), RELATIVE);
      start_pos = stepper.getCurrent();
    }

    if (stepper.getCurrent() <= stepper.getTarget()) {
      motors_flags_to_put.DOOR_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.DOOR_FLAG = 0;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.DOOR_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void open_wall() {
  motors_flags_to_put.WALL_UNFINISHED_MOVEMENT_FLAG = 1;
  int32_t start_pos;
  int parts_passed = 1;

  while (1) {
    
    if (!door_drive_class.tick()) {
      door_drive_class.setTarget((DOOR_DRIVE_DISTANCE), RELATIVE);
      start_pos = door_drive_class.getCurrent();
    }

    if (door_drive_class.getCurrent() >= door_drive_class.getTarget()) {
      motors_flags_to_put.WALL_UNFINISHED_MOVEMENT_FLAG = 0;
      motors_flags_to_put.WALL_FLAG = 0;
      for (int part = 1; part <= 128; part++) {
        motors_flags_to_put.WALL_DISTANCE_IN_PARTS_FLAG[part] = 0;
      }
      EEPROM.put(0, motors_flags_to_put);
      return;
    }
  }
}

void motors_movement() {
    switch (FSM_table[current_state][current_signal]) {
      case LEFT_CRATE_TO_RIGHT_CRATE_TRANSITION:
        move_left_drive_left();
        move_right_drive_left();
        current_state = RIGHT_CRATE_STATE;
        break;
      case LEFT_CRATE_TO_TOP_CRATE_TRANSITION:
        move_left_drive_left();
        move_top_drive_down();
        current_state = TOP_CRATE_STATE;
        break;
      case LEFT_CRATE_TO_BOTTOM_CRATE_TRANSITION:
        move_left_drive_left();
        move_bottom_drive_up();
        current_state = BOTTOM_CRATE_STATE;
        break;
      case RIGHT_CRATE_TO_LEFT_CRATE_TRANSITION:
        move_right_drive_right();
        move_left_drive_right();
        current_state = LEFT_CRATE_STATE;
        break;
      case RIGHT_CRATE_TO_TOP_CRATE_TRANSITION:
        move_right_drive_right();
        move_top_drive_down();
        current_state = TOP_CRATE_STATE;
        break;
      case RIGHT_CRATE_TO_BOTTOM_CRATE_TRANSITION:
        move_right_drive_right();
        move_bottom_drive_up();
        current_state = BOTTOM_CRATE_STATE;
        break;
      case TOP_CRATE_TO_LEFT_CRATE_TRANSITION:
        move_top_drive_up();
        move_left_drive_right();
        current_state = LEFT_CRATE_STATE;
        break;
      case TOP_CRATE_TO_RIGHT_CRATE_TRANSITION:
        move_top_drive_up();
        move_right_drive_left();
        current_state = RIGHT_CRATE_STATE;
        break;
      case TOP_CRATE_TO_BOTTOM_CRATE_TRANSITION:
        move_top_drive_up();
        move_bottom_drive_up();
        current_state = BOTTOM_CRATE_STATE;
        break;
      case BOTTOM_CRATE_TO_LEFT_CRATE_TRANSITION:
        move_bottom_drive_down();
        move_left_drive_right();
        current_state = LEFT_CRATE_STATE;
        break;
      case BOTTOM_CRATE_TO_RIGHT_CRATE_TRANSITION:
        move_bottom_drive_down();
        move_right_drive_left();
        current_state = RIGHT_CRATE_STATE;
        break;
      case BOTTOM_CRATE_TO_TOP_CRATE_TRANSITION:
        move_bottom_drive_down();
        move_top_drive_down();
        current_state = TOP_CRATE_STATE;
        break;
      case LEFT_CRATE_TO_CENTER_TRANSITION:
        move_left_drive_right();
        current_state = LEFT_CRATE_STATE;
        break;
      case RIGHT_CRATE_TO_CENTER_TRANSITION:
        move_right_drive_left();
        current_state = RIGHT_CRATE_STATE;
        break;
      case TOP_CRATE_TO_CENTER_TRANSITION:
        move_top_drive_down();
        current_state = TOP_CRATE_STATE;
        break;
      case BOTTOM_CRATE_TO_CENTER_TRANSITION:
        move_bottom_drive_up();
        current_state = BOTTOM_CRATE_STATE;
        break;
      case LEFT_CRATE_OUT_OF_CENTER_TRANSITION:
        move_left_drive_left();
        break;
      case RIGHT_CRATE_OUT_OF_CENTER_TRANSITION:
        move_right_drive_right();
        break;
      case TOP_CRATE_OUT_OF_CENTER_TRANSITION:
        move_top_drive_up();
        break;
      case BOTTOM_CRATE_OUT_OF_CENTER_TRANSITION:
        move_bottom_drive_down();
        break;
    }
}
