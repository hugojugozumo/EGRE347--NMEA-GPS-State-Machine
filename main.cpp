//******************************************************************
// Program #: Main file for NMEA State machine parser
//
// Programmer: Hugo Davalos/Matthew Gelber/Robert Klenke
//
// Due Date: NA
//
// EGRE 347, Spring 2022       Instructor: Robert Klenke
//
// Pledge: I have neither given nor received unauthorized aid on this program.
//
// Description: Reads in serial data, inputs it into our NMEA GPS state machine
//
// Input: command line argument of the desired serial port
//
// Output: none
//
//******************************************************************

using namespace std;

#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <wiringPi.h>
#include <csignal>

#include "LED_const.h" //the led init values
#include "NMEA_SM.h" //our state machine

bool RUNNING = true;

// Callback handler if CTRL-C signal is detected
void my_handler(int s) {
    cout << "Detected CTRL-C signal no. " << s << '\n';
    RUNNING = false;
}

int main(int argc, char *argv[])
{
	//unsigned char read_buff;
	char read_buff;
	finder state_mch; // state machine instantiation
	string tmp;
	bool chk=false;

   // Register a callback function to be called if the user presses CTRL-C
   signal(SIGINT, my_handler);

	// Initialize wiringPi and allow the use of BCM pin numbering
	wiringPiSetupGpio();

	// Setup the pins
	pinMode(red, OUTPUT);
	pinMode(yellow, OUTPUT);
	pinMode(green, OUTPUT);
	
	cout << argv[1] << endl;
	int sp = open(argv[1], O_RDONLY | O_NOCTTY | O_NDELAY);	//opens the serial port inputted as argument as read only

	if(sp < 0)
		cout << "unable to open port " << argv[1] << endl;
	else
		cout << "port successfully opened" << endl;

	
	while(RUNNING){
		int n = read(sp, &read_buff, sizeof(read_buff));
		if(n > 0) {	//make sure we don't get negative, will mess up checksum if so
			chk = state_mch.find(read_buff);	//send char read in to state machine
		}

		//will only output once we get full message
		if(chk == true){
		if(state_mch.getMsgtyp() == "GPGGA" ||state_mch.getMsgtyp() == "GPRMC"){
            digitalWrite(green, HIGH);
            digitalWrite(yellow, LOW);
            digitalWrite(red, LOW);
        }
        else if (state_mch.getMsgtyp() == "GPGSA"){
            digitalWrite(green, LOW);
            digitalWrite(yellow, HIGH);
            digitalWrite(red, LOW);
        }
		else{
			digitalWrite(green, LOW);
            digitalWrite(yellow, LOW);
            digitalWrite(red, HIGH);
		}
            
		}
		}

	close(sp);
}
