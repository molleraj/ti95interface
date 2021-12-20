#!/bin/bash
sudo stty -F /dev/ttyUSB0 500000 -icrnl -imaxbel \
-opost -onlcr \
-isig -icanon -iexten -echo -echoe -echok -echoctl -echoke
echo "Receiving from TI-95. Press Ctrl-C to end (after PRESS STOP)"
sudo cat /dev/ttyUSB0 > $1
