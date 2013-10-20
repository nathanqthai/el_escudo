PROG=blink

# compile parameters
CXX=avr-g++
F_CPU=16000000UL
MCU=atmega328p
CXXFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

# object creation paramters
OBJCOPY=avr-objcopy
BIN_FORMAT=ihex

# flashing parameters
AVRDUDE=avrdude -F -V
PROTOCOL=arduino
PART=ATMEGA328p
PORT=/dev/ttyUSB0
BAUD=57600

RM=rm -f

.SUFFIXES: .elf .hex

.cc.elf:
	$(CXX) $(CXXFLAGS) -I../src -o $@ $< ../src/el_escudo.cc

.elf.hex:
	$(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@

.PHONY: all
all: ${PROG}.hex

${PROG}.hex: ${PROG}.elf

${PROG}.elf: ${PROG}.cc

.PHONY: clean
clean:
	$(RM) ${PROG}.elf ${PROG}.hex

.PHONY: upload
upload: ${PROG}.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) \
	   -b $(BAUD) -U flash:w:${PROG}.hex
