#ifndef BUTTONS_H
#define BUTTONS_H

#include <JC_Button.h>
#include "fsm.h"
#include "bluetooth.h"
#include "motors.h"
#include "rfid.h"

/* Defining pins for buttons */

#define BUTTON1_PIN 26
#define BUTTON2_PIN 24
#define BUTTON3_PIN 22
#define BUTTON4_PIN 23
#define BUTTON5_PIN 25
#define BUTTON6_PIN 27

#define LEFT_BUTTON BUTTON1_PIN
#define TOP_BUTTON BUTTON2_PIN
#define RIGHT_BUTTON BUTTON3_PIN
#define BOTTOM_BUTTON BUTTON4_PIN

extern bool BUTTON_FLAG;

void buttons_init();
void buttons_check();

#endif /* BUTTONS_H */
