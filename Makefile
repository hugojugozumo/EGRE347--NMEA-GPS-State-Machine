all: prog1

prog1 : main.cpp NMEA_SM.cpp NMEA_SM.h
	g++ main.cpp NMEA_SM.cpp -lwiringPi -o prog1

clean:
	rm *.o prog*
