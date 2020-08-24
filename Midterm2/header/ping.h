
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static int heartbeat = 1;
static unsigned char tmpPoutput = 0x00;

//typedef enum ping_states { PInit, PingPulse                                           } ping_states;


/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit:
	    tmpPoutput = 0x00;
	    heartbeat = 1;
	    ping_state = PingPulse;
            break;
	case PingPulse:
	    heartbeat++; 
            ping_state = PingPulse;
	    break;
	default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;
	case PingPulse:
	    if(heartbeat % 10 == 1) {
		    tmpPoutput = 0x01;
	    } 
	    else {
		    tmpPoutput = 0x00;
	    } 
	    output = output >> 1;
	    output = output << 1;
	    output = output | tmpPoutput;

	   // output = (0xFE & output) | tmpPoutput;
	    break;
        default:
            break;
    }
}
