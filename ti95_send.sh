#!/bin/bash
# set serial conditions
sudo stty -F $2 500000 -icrnl -imaxbel \
-opost -onlcr \
-isig -icanon -iexten -echo -echoe -echok -echoctl -echoke
# set file byte start number
bytestart=0
# get file size
filesize=$(wc -c < $1)
# echo $filesize
# get filehandle for USB serial adapter or whatever (e.g., /dev/ttyUSB0)
#exec 4<$2
# as long as you have not reached EOF
while [ $bytestart -lt $filesize ]
do
# send 32 byte chunks
dd bs=1 skip=$bytestart count=32 if=$1 of=$2
#sleep 1
#sudo dd bs=1 skip=3100 count=32 if=lunarlander.95 of=/dev/ttyUSB0
# pause until Sent! is received
message="Unsent"
difference=$(($filesize-$bytestart))
echo $difference
if [ $difference -gt 32 ]
then
#until [ "$message" = "Sent!" ]
#do
#	read -n 5 message < /dev/ttyUSB0
#done
sleep 0.05
fi
# check if less than 32 bytes left in file
#if (($filesize-$bytestart)<32)
#	then
	# then send remaining bytes
#	difference=$filesize-$bytestart
#	dd bs=$difference if=$1
#fi
# wait, don't need to do this!
# dd automatically adjusts the final chunk size...
# go to beginning of loop until done
# increase bytestart counter by 32
bytestart=$((bytestart+32))
done
