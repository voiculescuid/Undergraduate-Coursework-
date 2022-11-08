all: build 

build: ksender kreceiver

ksender: functii.o ksender.o link_emulator/lib.o
	gcc -g ksender.o functii.o link_emulator/lib.o -o ksender

kreceiver: functii.o kreceiver.o link_emulator/lib.o
	gcc -g kreceiver.o functii.o link_emulator/lib.o -o kreceiver

functii.o: functii.c
	gcc -Wall -g -c functii.c

.c.o: 
	gcc -Wall -g -c $? 

clean:
	-rm -f *.o ksender kreceiver 
