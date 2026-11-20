#!/bin/bash

arg=$1

port=/dev/ttyUSB0
#baut=115200
baut=57600

comBaut=9600

#Log ms: date +%s%3N

mapfile -d '' srcfiles < <(find src -type f -name '*.c' -print0)

if [[ $arg == "clear" ]]; then
    rm -f bin/*

elif [[ $arg == "compile" ]]; then
    for f in ${srcfiles[@]}; do
        obj="bin/$(basename "$f" .c).o"
        avr-gcc -mmcu=atmega328pb -Os -std=gnu11 -Wall -Wextra -pedantic -fwrapv -c $f -o $obj
    done

    mapfile -d '' objfiles < <(find bin -type f -name '*.o' -print0)
    avr-gcc -mmcu=atmega328pb -Os -std=gnu11 -Wall -Wextra -pedantic -fwrapv ${objfiles[@]} -o bin/main.elf

    avr-objcopy -O ihex -R .eeprom bin/main.elf bin/main.hex

elif [[ $arg == "flash" ]]; then
    #avrdude -v -patmega328p -carduino -P$port -b$baut -Uflash:w:bin/main.hex:i
    avrdude -v -p atmega328pb -c usbasp -Uflash:w:bin/main.hex:i

elif [[ $arg == "sPort" ]]; then
    stty -F $port $comBaut raw -echo -hupcl

else
    #bash .build.sh "sPort"
    bash .build.sh "clear"
    bash .build.sh "compile"
    bash .build.sh "flash"
fi
