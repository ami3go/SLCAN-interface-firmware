#include "src/mcp2515/can.h"

//RICM hearbeat messages 300ms
static struct can_frame KeepAlive1_cost = {0x0FF,8,0x00,0x00,0x07,0x80,0x00,0x00,0x00,0x00}; // keep RICM Alive massage with PM7
static struct can_frame KeepAlive2_cost = {0x59E,8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // keep RICM Alive 

//RICM DTC related massages 
static struct can_frame ReadAllDTC_cost =   {0x7B5,8,0x03,0x19,0x02,0xFF,0x00,0x00,0x00,0x00}; // 
static struct can_frame ReadIntFault_cost = {0x7B5,8,0x03,0x22,0xD7,0x05,0x00,0x00,0x00,0x00}; //  
static struct can_frame ReadByID_cost =     {0x7B5,8,0x03,0x22,0x40,0x44,0x00,0x00,0x00,0x00}; //  
 
//MLA heatbeat massages 
static struct can_frame KeepAlive3_cost =     {0x400,8,0x48,0x02,0x0E,0x00,0x00,0x41,0x54,0x2A}; //  
  