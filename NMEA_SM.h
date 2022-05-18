//******************************************************************
// Program #: NMEA State Machine Header file
//
// Programmer: Hugo Davalos
//
// Due Date: NA
//
// EGRE 347, Spring 2022       Instructor: Robert Klenke
//
// Pledge: I have neither given nor received unauthorized aid on this program.
//
// Description: Header file for NMEA state machine parser
//
// Input: none
//
// Output: none
//
//******************************************************************

using namespace std;

enum find_states{INIT, rd, chksm1, chksm2, calc_chksm}; //defines our states

// Description:
// Defines our state machine
//
// Date Members:
// [STATES] = INIT, rd, chksm1, rd_calc_chksm, print (enum class that defines our states)
// msgtype - used in main to light LEDs
// msg - contains our message string
// chksum - holds our check sum val
//
// Methods:
// find - defines our state machine, return bool if a whole message is correctly read
// getMsgtyp - returns the message type (first 5 bytes)
class finder
{
	private:
		enum find_states State;		// Holds current state the traffic light is in
		string msg;	//stores the whole message
    	string chksum;	//stores our two check sum bytes
    	string msgtype;	//stores whole transmitted message
		
	public:
		finder();				// Constructor
		
		~finder();					// Destructor
	
		string getMsgtyp();			//returns the message type
	
		bool find(char c);			// Main implementation for the state machine
};
