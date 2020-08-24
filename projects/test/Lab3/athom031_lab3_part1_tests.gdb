# Test file for "Lab3_bitManip"


echo ======================================================\n
echo Running all tests..."\n\n

#check 0 input basically to check if while loop compile
test "PINA: 0x00, PINB: 0x00 => PORTC: 0x00"
setPINA 0x00
setPINB 0x00
continue 5
expectPORTC 0x00
checkResult

#check all 1's, both end cases work
test "PINA: 0xFF, PINB: 0xFF => PORTC: 0x10"
setPINA 0xFF
setPINB 0xFF
continue 5
expectPORTC 0x10
checkResult

test "PINA: 0x55, PINB: 0xAA => PORTC: 0x08"
setPINA 0x55
setPINB 0xAA
continue 5
expectPORTC 0x08
checkResult

test "PINA: 0x44, PINB: 0x22 => PORTC: 0x04"
setPINA 0x44
setPINB 0x22
continue 5
expectPORTC 0x04
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
