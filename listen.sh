#!/bin/bash

# halt on error
set -e

DEVICE=$1
BAUDRATE=$2

# start cat in background and record the PID
cat ${DEVICE} &
PID=$!

# trap exit and stop the cat process (eg: ctrl-c)
# we set this up before continuing in case we
# we have to clean up after an error
cleanup()
{
  kill $PID 2> /dev/null
}
trap cleanup EXIT

# Have to change baudrate after
# starting cat for it to stick
stty -f ${DEVICE} speed ${BAUDRATE}

# loop while the cat process is running
while kill -0 $PID 2> /dev/null; do
  # don't do anything
  sleep 1
done

# cat process has stopped so clear the trap
trap - EXIT
