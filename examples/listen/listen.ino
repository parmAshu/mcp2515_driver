#include "mcp2515_driver.h"

mcp2515_driver_config chipConfig = {
  .ss_pin = 10
};

static CAN_FRAME FRM;

void log_can_frame(uint8_t buff)
{
	Serial.print("ID: ");
	Serial.println(FRM.ID);

	Serial.print("DATA: ");
	for(uint8_t i=0; i<FRM.DLC; i++)
	{
		Serial.print(FRM.DATA[i], HEX);		
		if(i<FRM.DLC-1) Serial.print(", ");
	}
	Serial.println();

	Serial.print("buff: ");
	Serial.print(buff);

	Serial.println("\n\n");
}

void setup() 
{
  Serial.begin(9600);

  canBegin(&chipConfig, 500);
  canDisableFilterRX(0);
  canDisableFilterRX(1);

  Serial.println("CAN chip initialized");

  delay(100);
}

void loop() 
{
	if(canIsFilledRX(0))
	{
		FRM=canGetFrame_wID(0);
		log_can_frame(0);
	}

	if(canIsFilledRX(1))
	{
		FRM=canGetFrame_wID(1);
		log_can_frame(1);
	}
}