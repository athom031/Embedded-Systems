
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
// while no earthquake wait
// when in earthquake observe current direction
// upon a change in direction, save the two and copmare
// if comparison shows zerocrossing output while somehow also keeping track of change in direction


/*complete the state machine*/

void Detect_ZC()
{
    switch(detect_zc_state)
    {
        case DZCInit:
	    	
            break;
        
        default:
            detect_zc_state = DZCInit;
            break;
    }
    switch(detect_zc_state)
    {
        case DZCInit:
            break;
        default:
            break;
    }
}
