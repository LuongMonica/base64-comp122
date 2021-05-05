CCFLAGS=-g
BASE64=/usr/bin/base64


base64: driver.o base64.o
	$(CC) $(CCFLAGS) -o base64 driver.o base64.o

driver.o: driver.c

base64.o: base64.c base64.h
	$(CC) $(CCFLAGS) -c base64.c

clean:
	rm -f *.o *~ base64


test: base64
	./base64.tester
