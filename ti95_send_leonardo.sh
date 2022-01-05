#!/bin/bash
# set serial conditions
sudo stty -F $2 460800 -icrnl -imaxbel \
-opost -onlcr \
-isig -icanon -iexten -echo -echoe -echok -echoctl -echoke
# now send to the TI-95
echo "Sending to TI-95..."
sudo cat $1 > $2
