CC= g++
CFLAGS= -Wall -Werror -pedantic -O3 -std=c++14
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:	NBody

NBody:	Universe.o CelestialBody.o
	$(CC) Universe.o CelestialBody.o -o NBody $(SFMLFLAGS)

Universe.o:	Universe.cpp CelestialBody.h
	$(CC) -c Universe.cpp CelestialBody.h $(CFLAGS)

CelestialBody.o: CelestialBody.cpp CelestialBody.h
	$(CC) -c CelestialBody.cpp CelestialBody.h $(CFLAGS)

clean:
	rm *.o
	rm *.gch
	rm NBody
