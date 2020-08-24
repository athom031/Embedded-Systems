//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static unsigned char tmpAoutput = 0x00;
static unsigned char currMax = 0x00;
static unsigned char currAmp = 0x00;
/* complete the state machine. */
//State ideas wait for earthquake
//when on set current max and output current max
void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
	    tmpAoutput = 0x00;
	    detect_max_amp_state = EQ_WAIT;
            break;
	case EQ_WAIT:
	    if(output & 0x02) {
		    currMax = 0;
		    tmpAoutput = currMax;
		    detect_max_amp_state = OUTPUT_MAX_AMP;
	    } 
	    else { //means theres no current earthquake on going
        	    detect_max_amp_state = EQ_WAIT;
	    }
	    break;
	case OUTPUT_MAX_AMP:
	    if(output & 0x02) {
		    detect_max_amp_state = OUTPUT_MAX_AMP;
	    } 
	    else { //earthquake has stopped occurring
		    detect_max_amp_state = EQ_WAIT;
		    currMax = 0;
		    tmpAoutput = currMax;
	    }
	    break;
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;
	case EQ_WAIT:
	    output = (output & 0x03) | tmpAoutput;
	    break;
	case OUTPUT_MAX_AMP:
	    currAmp = (~PINA & 0xF8);
	    if(currAmp > currMax) {
		    currMax = currAmp;
	    }
	    tmpAoutput = currMax;
	    output = (output & 0x03) | tmpAoutput;
	    break;
        default:
            break;
    }
}
