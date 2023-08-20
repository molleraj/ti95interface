#!/bin/bash
# set serial conditions
# removed sudo from stty and cat commands below after testing on Ubuntu 22.04
stty -F $2 460800 -icrnl -imaxbel \
-opost -onlcr \
-isig -icanon -iexten -echo -echoe -echok -echoctl -echoke
# now send to the TI-95
echo "Sending to TI-95..."
cat $1 > $2
