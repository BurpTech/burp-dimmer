#!/bin/bash

DEVICE=$1
BAUDRATE=$2

# start cat in background and record the PID
cat ${DEVICE} &
PID=$!

# Have to change baudrate after
# starting cat for it to stick
stty -f ${DEVICE} speed ${BAUDRATE}

cleanup()
{
  kill $PID 2> /dev/null
}

# trap exit and stop the cat process (eg: ctrl-c)
trap cleanup EXIT

# loop while the cat process is running
while kill -0 $PID 2> /dev/null; do
  # don't do anything
  sleep 1
done

# cat process has stopped so clear the trap
trap - EXIT
