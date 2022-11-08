all: build

build: Frati ursi

Frati: Frati.java
	javac Frati.java

ursi: ursi.c
	gcc ursi.c -o ursi

run-p1:
	java Frati

run-p2:
	./ursi

clean:
	-rm -f ursi
	-rm -f *.class
