#include "rfid.h"

WIEGAND WG;

static unsigned long card_id_1 = 15587624;
static unsigned long card_id_2 = 15587605;
static unsigned long card_id_3 = 15567461;
static unsigned long card_id_4 = 15567495;
static unsigned long card_id_5 = 15567446;

/* RFID functions */

void RFID_init() {
  WG.begin(RFID_WIEGAND_D0, RFID_WIEGAND_D1);
}

void RFID_parser() {
  if(WG.available())
	{
    unsigned long current_code = WG.getCode();
    if (!OPENED_FLAG && (current_code == card_id_1 || current_code == card_id_2 || current_code == card_id_3 || current_code == card_id_4 || current_code == card_id_5)) 
    {
      digitalWrite(RELAY_PIN, HIGH);

      delay(100);
      
      open_wall();
      open_door();
      Serial.println("Opened!");

      digitalWrite(LED_PIN, HIGH);

      OPENED_FLAG = 1;
      
      return;
    }
    
    if (OPENED_FLAG && (current_code == card_id_1 || current_code == card_id_2 || current_code == card_id_3 || current_code == card_id_4 || current_code == card_id_5))
    {
      close_door();
      close_wall();
  
      current_signal = TOP_CRATE_SIGNAL;
      motors_movement();
  
      OPENED_FLAG = 0;
  
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
      return;
    }
	}
}
