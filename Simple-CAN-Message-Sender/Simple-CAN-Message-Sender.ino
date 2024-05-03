#include <SPI.h>
#include "src/mcp2515/mcp2515.h"
#include "CAN_msg_db.h"

MCP2515 mcp2515(10);
unsigned int i;

void setup() {
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  for( i = 0; i < 4; i++ ){
  mcp2515.sendMessage(&KeepAlive1_cost);
  delay(100);
  mcp2515.sendMessage(&KeepAlive2_cost);
  delay(100);
  mcp2515.sendMessage(&KeepAlive3_cost);
  delay(100);
  }
   mcp2515.sendMessage(&ReadAllDTC_cost);
   delay(10);
   mcp2515.sendMessage(&ReadIntFault_cost);
   delay(10);
   mcp2515.sendMessage(&ReadByID_cost);
   delay(10);
}
