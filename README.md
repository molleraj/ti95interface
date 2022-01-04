# CIduino7: TI-95 Arduino Replacement Cassette Interface

Watch the demo here! https://www.youtube.com/watch?v=DMReYWH7o-4

All files in this repository are related to the Arduino Uno/Leonardo-based replacement TI-95 cassette interface I am building. I decided to call it a CIduino7 as it replaces the original TI cassette interface for the 74/95, the TI CI-7. This interface will let you send and receive TI-95 programs from a Linux machine. Theoretically it should work with the TI-74 BasiCalc and CC-40 as these share the same Dockbus and Hexbus physical interfaces, respectively, and probably similar cassette protocols.

Currently only the Arduino Leonardo works for transmission in both directions (receiving from and sending to the TI-95), probably because it properly emulates hardware handshaking.

Plans for building the interface will be added in the future. I will be selling pre-built interfaces soon. The primary issue right now is to document the tape file format.

Schematic (Arduino Uno/Leonardo to TI-95 Dockbus):  
<pre>
GND      -> 10  
(PWM) 10 ->  6  
(PWM) 9  ->  3  
</pre>

TI-95 operation:

Press I/O to access input/output menus first. Then select TAP for tape storage operations (F1). Select RD (F1) to read a file from cassette (PC/Arduino) or WRT (F2) to write a file to cassette (PC/Arduino). Only run scripts on the computer (listed below) after pressing OK at "PRESS PLAY" or before pressing OK at "PRESS RECORD" prompts.

Included files:

ti95_receive.sh - to receive files from the TI-95 on the PC.  
Syntax: `ti95_receive.sh </dev/ttyUSBx for Arduino> <output filename>` 

ti95_send.sh - to send files from the PC to the TI-95.  
Syntax: `ti95_send.sh <file to send> </dev/ttyUSBx for Arduino>` 

ti95_send_2.sh - to send files from the PC to the TI-95, with adjustable chunk size (bytes per transfer) and delay between sending chunks.  
Syntax: `ti95_send_2.sh <file to send> </dev/ttyUSBx for Arduino> <chunk size> <delay>`   

ti95_send_leonardo.sh - to send files from the PC to the TI-95 with the Leonardo-based interface. Currently the only working send script.
Syntax: `ti95_send_leonardo.sh <file to send> </dev/ttyUSBx for Arduino>`
  
ti95_interface_uno.ino - sketch with send/receive PWM routines for Arduino Uno. 

ti95_interface_leonardo.ino - sketch with send/receive PWM routines for Arduino Leonardo.

ti95_interface_leonardo_final.ino - final, cleaned up sketch with send/receive PWM routines for Arduino Leonardo.
  
lunarlander.95 - sample program received with ti95_receive.sh.  
