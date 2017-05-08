# 8-Bit Utils
## Summary
This program is designed to be used with my 8 bit computer. Its purpose is to gather the state of the computer through the data bus and control pins, and also to program the memory.
## Programmer
After sending `0x50`, the program goes into programming mode and returns `0x52`. After sending the memory and data values, it will return `0x52` and programs the RAM.

## Debugger
Currently the debugger only sends the values of the data bus, but eventually I might be able to change the direction of the programming bus to also get the control pins.

## Commands
* `0xF0` Enter programming mode.
* `0xFF` Enter as address to exit programming mode
* `0x44` Get the data bus
