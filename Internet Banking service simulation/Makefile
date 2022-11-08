CC=gcc
LIBSOCKET=-lnsl
CCFLAGS=-Wall -g
SRV=server
CLT=client
FCT=functions

all: $(SRV) $(CLT)

$(SRV):$(SRV).c
	$(CC) -o $(SRV) $(LIBSOCKET) $(SRV).c $(FCT).c

$(CLT):	$(CLT).c
	$(CC) -o $(CLT) $(LIBSOCKET) $(CLT).c $(FCT).c

clean:
	rm -f *.o *~
	rm -f $(SRV) $(CLT)
	rm -f *.log

