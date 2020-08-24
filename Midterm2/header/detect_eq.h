//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

//read pins A3-A7 to see if there is an earthquake
//if there is output 1
//else output 0  FOR B1
static unsigned char eqTmpA = 0x00;
static unsigned char tmpDoutput = 0x00;

/*complete the state machine*/

void Detect_EQ()
{
    eqTmpA = (~PINA & 0xF8);
    eqTmpA = eqTmpA >> 3;
    switch(detect_eq_state)
    {
        case DEQInit:
	    tmpDoutput = 0x00;
	    detect_eq_state = DEQRead;
            //init variable(s) here.
            break;
	case DEQRead:
	    detect_eq_state = DEQRead;
	    break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case DEQRead:
	    if(eqTmpA) {
		    tmpDoutput = 0x02;
	    }
	    else {
		    tmpDoutput = 0x00;
	    }
	    output = (output & 0xFD) | tmpDoutput;
	    break;
        default:
            break;
    }
}
