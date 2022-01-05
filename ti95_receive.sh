#!/bin/bash
sudo stty -F $1 460800 -icrnl -imaxbel \
-opost -onlcr \
-isig -icanon -iexten -echo -echoe -echok -echoctl -echoke
echo "Receiving from TI-95. Press Ctrl-C to end (after PRESS STOP)"
sudo cat $1 > $2
