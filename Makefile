PRJNAME	= BusMonitor
OBJNAME	= BusMonitor
all: 
	avr-gcc -g -Os -mmcu=atmega162 -c $(PRJNAME).c 
	avr-gcc -g -mmcu=atmega162 -o $(OBJNAME).elf $(OBJNAME).o 
	avr-objdump -h -S $(OBJNAME).elf > $(OBJNAME).lst
	avr-gcc -g -mmcu=atmega162 -Wl,-Map,$(OBJNAME).map -o $(OBJNAME).elf $(OBJNAME).o
	avr-objcopy -j .text -j .data -O ihex $(OBJNAME).elf $(OBJNAME).hex
	mv *.o *.elf *.lst *.map bin
	mv *.hex build
	
clean:
	cd bin
	rm -rf *.o $(PRJNAME).elf *.eps *.png *.pdf *.bak
	rm -rf *.lst *.map
	cd build 
	rm -rf *.hex
