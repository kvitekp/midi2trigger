@call \DIY\SetVars.cmd
 make -f midi2trigger\makefile %1
 if errorlevel 1 goto EOF
 if {%1} == {clean} goto EOF
 avr-objdump -h -S build\midi2trigger\midi2trigger.elf > build\midi2trigger\midi2trigger.lst
 set path=%path%;C:\Program Files (x86)\Atmel\AVR Tools\STK500
 stk500 -cUSB -dATmega328p -I4Mhz -e -ifbuild\midi2trigger\midi2trigger.hex -pf -vf
:EOF
