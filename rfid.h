#ifndef RFID_H
#define RFID_H

#include "Wiegand.h"
#include "bluetooth.h"
#include "fsm.h"

/* Defining RFID module pins and more */

#define RFID_WIEGAND_D0 3
#define RFID_WIEGAND_D1 2

#define LED_PIN 20
#define RELAY_PIN 21

extern bool RFID_VALID_CARD_FLAG;
extern bool RFID_OFF_FLAG;

void RFID_init();
void RFID_parser();

#endif /* RFID_H */
