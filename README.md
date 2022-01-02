# TI-95 Arduino Replacement Cassette Interface

All files in this repository are related to the Arduino Uno/Leonardo-based replacement TI-95 cassette interface I am building. This interface will let you send and receive TI-95 programs from a Linux machine.

Currently only the Arduino Leonardo works for transmission in both directions (receiving from and sending to the TI-95), probably because it properly emulates hardware handshaking.

Plans for building the interface will be added in the future. I will be selling pre-built interfaces soon. The primary issue right now is to fix the PC to TI-95 send script/send routines.

Schematic (Arduino to TI-95 Dockbus):  
<pre>
GND     -> 10  
(PWM) 7 ->  6  
(PWM) 6 ->  3  
</pre>

ti95_receive.sh - to receive files from the TI-95 on the PC.  
Syntax: `ti95_receive.sh <output_filename>` 

ti95_send.sh - to send files from the PC to the TI-95.  
Syntax: `ti95_send.sh <file to send> </dev/ttyUSBx for Arduino>` 

ti95_send_2.sh - to send files from the PC to the TI-95, with adjustable chunk size (bytes per transfer) and delay between sending chunks.  
Syntax: `ti95_send_2.sh <file to send> </dev/ttyUSBx for Arduino> <chunk size> <delay>`   
  
ti95_interface_uno.ino - sketch with send/receive PWM routines for Arduino Uno. 

ti95_interface_leonardo.ino - sketch with send/receive PWM routines for Arduino Leonardo.
  
lunarlander.95 - sample program received with ti95_receive.sh.  
