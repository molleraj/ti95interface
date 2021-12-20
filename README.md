# TI-95 Arduino Replacement Cassette Interface

All files in this repository related to the Arduino Uno-based replacment TI-95 cassette interface I am building. This interface will let you send and receive TI-95 programs from a Linux machine.

ti95_receive.sh - to receive files from the TI-95 to the PC
ti95_send.sh - to send files from the PC to the TI-95
ti95_send_2.sh - to send files from the PC to the TI-95, with adjustable chunk size (bytes per transfer) and delay between sending chunks.
ti95_interface_uno.ino - sketch with send/receive PWM routines for Arduino Uno
