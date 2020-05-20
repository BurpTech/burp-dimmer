.PHONY: all compile upload listen clean

include local.mk

# check that the serial device has been
# specified in local.mk
ifeq ($(SERIAL_DEVICE),)
$(error SERIAL_DEVICE is not set)
endif

SKETCH:=sketch

FQBN:=esp8266:esp8266:d1_mini
FQBN_FILE:=$(subst :,.,${FQBN})

BAUDRATE:=115200

ifdef UPLOAD_FLAGS
	UPLOAD_FQBN:=${FQBN}:${UPLOAD_FLAGS}
else
	UPLOAD_FQBN:=${FQBN}
endif

all: upload listen

compile:
	arduino-cli compile --fqbn ${FQBN} ${SKETCH}

upload: compile
	arduino-cli upload -p ${SERIAL_DEVICE} --fqbn ${UPLOAD_FQBN} ${SKETCH}

listen:
	./listen.sh ${SERIAL_DEVICE} ${BAUDRATE}

clean:
	rm ${SKETCH}/${SKETCH}.${FQBN_FILE}.elf
	rm ${SKETCH}/${SKETCH}.${FQBN_FILE}.bin
