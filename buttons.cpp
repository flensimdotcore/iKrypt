#include "buttons.h"

bool BUTTON_FLAG = 0;

Button main_button(MAIN_BUTTON, 50, false, false);
Button left_button(LEFT_BUTTON, 50, false, false);
Button right_button(RIGHT_BUTTON, 50, false, false);
Button top_button(TOP_BUTTON, 50, false, false);
Button bottom_button(BOTTOM_BUTTON, 50, false, false);

void buttons_init() {
  main_button.begin();
  left_button.begin();
  right_button.begin();
  top_button.begin();
  bottom_button.begin();
}

void buttons_check() {
  main_button.read();
  left_button.read();
  right_button.read();
  top_button.read();
  bottom_button.read();

  if (main_button.isPressed() && left_button.isPressed()) {
    current_signal = LEFT_CRATE_SIGNAL;
    BUTTON_FLAG = 1;
  } else if (main_button.isPressed() && right_button.isPressed()) {
    current_signal = RIGHT_CRATE_SIGNAL;
    BUTTON_FLAG = 1;
  } else if (main_button.isPressed() && top_button.isPressed()) {
    current_signal = TOP_CRATE_SIGNAL;
    BUTTON_FLAG = 1;
  } else if (main_button.isPressed() && bottom_button.isPressed()) {
    current_signal = BOTTOM_CRATE_SIGNAL;
    BUTTON_FLAG = 1;
  } else {
    BUTTON_FLAG = 0;
  }
}