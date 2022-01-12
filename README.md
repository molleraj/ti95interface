# CIduino7: TI-95 Arduino Replacement Cassette Interface

Watch the demo here! https://www.youtube.com/watch?v=DMReYWH7o-4

![image](/ciduino7-5.jpg)

All files in this repository are related to the Arduino Uno/Leonardo-based replacement TI-95 cassette interface I am building. I decided to call it a CIduino7 as it replaces the original TI cassette interface for the 74/95, the TI CI-7. This interface will let you send and receive TI-95 programs from a Linux machine. Theoretically it should work with the TI-74 BasiCalc and CC-40 as these share the same Dockbus and Hexbus physical interfaces, respectively, and probably similar cassette protocols.

Currently only the Arduino Leonardo works for transmission in both directions (receiving from and sending to the TI-95), probably because it properly emulates hardware handshaking.

Plans for building the interface are described below. I am now selling pre-built interfaces for $25 plus shipping. I offer a 14 day warranty - you can return the unit within two weeks of purchase for a refund if it's defective or damaged.

Schematic (Arduino Uno/Leonardo to TI-95 Dockbus):  
<pre>
GND      -> 10  
(PWM) 10 ->  6  
(PWM) 9  ->  3  
</pre>

For reference, this is the Dockbus orientation from the back of the TI-95/TI-74. Look on the back of the calculator for a square notch. Pin 1 is closest to the square notch and pin 10 is furthest from it.

<pre>
Left side of calculator - square notch - 1--------10 (Dockbus) - right side of calculator
</pre>

![image](/ciduino7-7.jpg)

I constructed my CIduino7  (shown in the image above) by connecting the male end of three male to female 20 cm Dupont jumper wires to the female GND and PWM pins of an Arduino Leonardo (specified above). I connected the female ends to the 3, 6, and 10 male pins of two stacked Arduino female headers wrapped on the outside with electrical tape. This wrapped, stacked header could then be inserted into the Dockbus port on the rear of the TI-95 (and TI-74).

TI-95 operation:

Press I/O to access input/output menus first. Then select TAP for tape storage operations (F1). Select RD (F1) to read a file from cassette (PC/Arduino) or WRT (F2) to write a file to cassette (PC/Arduino). Only run scripts on the computer (listed below) after pressing OK at "PRESS PLAY" or before pressing OK at "PRESS RECORD" prompts.

PC operation:

Scripts are Linux compatible, tested on a GalliumOS (Ubuntu 18.04) Chromebook. They have not yet been tested on a Mac (Unix), but they are expected to be compatible with Unix as well. Baud rate was reduced from 500000 to 460800 to make the sketch compatible with the terminal emulator RealTerm on Windows. The serial port should be set to that of the Arduino Leonardo and 460800 baud/8 bits/no stop bit/1 parity bit (460800 8N1). Send and receive TI-95 tape format files with hex upload (send to TI-95) and logging (receive from TI-95) in RealTerm (confirmed to work on Windows 10). You can download RealTerm here: https://sourceforge.net/projects/realterm/

Note that files some times get corrupted in transfer, usually after changing serial settings or running multiple programs that access the serial port. Make sure to inspect your file with a hex editor like hexedit, bless, xxd, or HxD. If your three letter header (e.g., HLO, MST, MLD) is incorrect or the data otherwise doesn't correspond to your program, unplug the adapter, plug it in again, and repeat the file transfer. Make sure your adapter is set to 460800 8n1. This has resolved issues in every case for me.

Tape file format:

Now that the format is documented, it will be possible to compile keystroke listings (typed in a certain format) to tape format and back. I am currently implementing a simple keystroke listing compiler in bash. So far I have provided the compiler plan in compiler_steps.txt.

1208 zero bytes (zero padding; time zero/one bit pulses on TI-95)  

FF byte  
00 05 00 00 05 84 8E byte header (unknown, constant in all programs)  
Eight 00 bytes  

Repeat previous structure

FF byte  
Total bytes low byte, total bytes high byte, three byte ASCII filename, checksum of previous five bytes  
Eight 00 bytes  

Repeat previous structure

1208 zero bytes (zero padding; time zero/one bit pulses on TI-95)

FF byte  
Total bytes high byte, total bytes low byte, 00 byte, number of full (64 byte) records, number of bytes in final incomplete (<64 byte record) record (if present), 82 byte, checksum of previous six bytes  
Eight 00 bytes  

Repeat previous structure

FF byte  
64 byte record (reverse program order!)  
Checksum of previous 64 bytes  
Eight 00 bytes  

Repeat previous structure

... (repeat until all complete records encoded)

FF byte  
Final record (under 64 bytes)  
Checksum of remaining previous bytes  
Eight 00 bytes  

Repeat previous structure

FF byte (closing)

Remember - all listings are in reverse order in the tape file. It also looks like the final incomplete record is only formed in multiples of 16 (10, 20, and 30h in the examples I have seen). Extra 00 bytes are placed in the beginning of the first complete record as needed (after the end of the program).

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

&copy; Abraham Moller, 2022
