# SLCAN-interface-firmware 
---

CAN BUS interface firmware based on Arduino and SPI MCP2515. It is positoion as cheap easy to build interface.  

- https://github.com/ami3go/SLCAN-interface-hardware
- Numerous other MCP2515 based CAN BUS modules from ebay and aliexpress work well to

This software implements CAN ASCII / Serial CAN / SLCAN protocol compatible with Lawicel CAN232/CANUSB. 

---

As for PC counterpart software I personally used and can recommend few tools:

1) [**Python pyCAN**]. Most popular Python library for CAN interfaces
   - https://python-can.readthedocs.io
   - https://github.com/ami3go/SLCAN-python-examples
  
2) [**Linux**] SLCAN/SocketCAN can be used https://github.com/linux-can/can-utils. See details in the end of this README file
    
3) [**Windows**] CANHacker tool v.2.00.01 (by fuchs) to sniff and visualize data on the bus.
    [CANHackerV2.00.01.exe](https://github.com/latonita/arduino-canbus-monitor/raw/master/CANHackerV2.00.01.exe)

5) [**Windows/Linux**] CAN-COOL (by MHS Elektronik), open source, but unfortunaly available only in German.
   -  [Download link](http://www.mhs-elektronik.de/index.php?module=content&action=show&page=can_cool)  (Make sure you select RS232 and SL-CAN protocol and then click hardware bus reset icon on a toolbar)
   -  [Git Hub repository](https://github.com/MHS-Elektronik/OBD-Display)

---

This code forked from https://github.com/Seeed-Studio/CAN_BUS_Shield.

Copyright (C) 2015,2016 Anton Viktorov <latonita@yandex.ru>

---

See protocol definition here: 
- http://www.can232.com/docs/can232_v3.pdf
- http://www.can232.com/docs/canusb_manual.pdf

---

Commands not supported/not implemented:  
- s, W, M, m, U.

Commands modified:
-  S - supports not declared 83.3 rate 
-  F - returns MCP2515 error flags
-  Z - extra Z2 option enables 4 byte timestamp vs standard 2 byte (60000ms max)
  
```
CMD | IMPLEMENTED | SYNTAX               | DESCRIPTION
------------------------------------------------------------------------------------------------------------
'S' |   YES+      |   Sn[CR]               Setup with standard CAN bit-rates where n is 0-8.
    |             |                        S0 10Kbit          S4 125Kbit         S8 1Mbit
    |             |                        S1 20Kbit          S5 250Kbit         S9 83.3Kbit
    |             |                        S2 50Kbit          S6 500Kbit
    |             |                        S3 100Kbit         S7 800Kbit
's' |    -        |   sxxyy[CR]            Setup with BTR0/BTR1 CAN bit-rates where xx and yy is a hex value.
'O' |   YES       |   O[CR]                Open the CAN channel in normal mode (sending & receiving).
'L' |   YES       |   L[CR]                Open the CAN channel in listen only mode (receiving).
'C' |   YES       |   C[CR]                Close the CAN channel.
't' |   YES       |   tiiildd...[CR]       Transmit a standard (11bit) CAN frame.
'T' |   YES       |   Tiiiiiiiildd...[CR]  Transmit an extended (29bit) CAN frame
'r' |   YES       |   riiil[CR]            Transmit an standard RTR (11bit) CAN frame.
'R' |   YES       |   Riiiiiiiil[CR]       Transmit an extended RTR (29bit) CAN frame.
'P' |   YES       |   P[CR]                Poll incomming FIFO for CAN frames (single poll)
'A' |   YES       |   A[CR]                Polls incomming FIFO for CAN frames (all pending frames)
'F' |   YES+      |   F[CR]                Read Status Flags.
'X' |   YES       |   Xn[CR]               Sets Auto Poll/Send ON/OFF for received frames.
'W' |    -        |   Wn[CR]               Filter mode setting. By default CAN232 works in dual filter mode (0) and is backwards compatible with previous CAN232 versions.
'M' |    -        |   Mxxxxxxxx[CR]        Sets Acceptance Code Register (ACn Register of SJA1000). // we use MCP2515, not supported
'm' |    -        |   mxxxxxxxx[CR]        Sets Acceptance Mask Register (AMn Register of SJA1000). // we use MCP2515, not supported
'U' |   YES       |   Un[CR]               Setup UART with a new baud rate where n is 0-6.
'V' |   YES       |   v[CR]                Get Version number of both CAN232 hardware and software
'v' |   YES       |   V[CR]                Get Version number of both CAN232 hardware and software
'N' |   YES       |   N[CR]                Get Serial number of the CAN232.
'Z' |   YES+      |   Zn[CR]               Sets Time Stamp ON/OFF for received frames only. EXTENSION to LAWICEL: Z2 - millis() timestamp w/o standard 60000ms cycle
'Q' |   YES  todo |   Qn[CR]               Auto Startup feature (from power on). 

```

## Linux SLCAN instructions
### Prerequisites
Install `can-utils` first. 
On Ubuntu and other Debian-based distros `can-utils` package is included into standard repositories:
```
sudo apt install can-utils
```
For other distros please follow respective instructions, start from here https://github.com/linux-can/can-utils

### Create CAN device
Linux have different naming for serial port based on implenetation:
- USB-to-Serial ICs, such as CH340 get /dev/ttyUSBx where x=[1,2,3...]
- Micro with intergrated USB, such as ATmega32u4 get /dev/ttyACMx where x=[1,2,3...]
```
sudo slcan_attach -f -s4 -o /dev/ttyUSB0 
sudo slcand -S 115200 /dev/ttyUSB0 can0  
sudo ifconfig can0 up
```
where 115200 is port speed, `/dev/ttyUSB0` - name of your arduino device. can be different

### To dump running traffic 
```
candump can0
```

### To delete CAN device
```
sudo ifconfig can0 down
sudo killall slcand
```


