# Test file for "Lab2_introToAVR"



echo ======================================================\n
echo Running all tests..."\n\n

echo any value in first nibble shouldnt affect output\n
test "PINA: 0xF0 => PORTC: 0x04"
setPINA 0xF0
continue 5
expectPORTC 0x04
checkResult

echo no 1's should output 4 free parking spaces free\n

test "PINA: 0x00 => PORTC: 0x04"
setPINA 0x00
continue 5
expectPORTC 0x04
checkResult


echo one 1 should output 3 free parking spaces\n
#possible: 1000 0100 0010 0001 
test "PINA: 0x08 => PORTC: 0x03"
setPINA 0x08
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x04 => PORTC: 0x03"
setPINA 0x04
continue 5
expectPORTC 0x03
checkResult

echo two 1's will have 2 free parking spaces\n
#possible: 1100 1010 1001 0110 0101 0011
test "PINA: 0x09 => PORTC: 0x02"
setPINA 0x09
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x06 => PORTC: 0x02"
setPINA 0x06
continue 5
expectPORTC 0x02
checkResult

echo three 1's will have 1 parking space\n
#possible: 1110 1101 1011 0111
test "PINA: 0x0E => PORTC: 0x01"
setPINA 0x0E
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x07 => PORTC: 0x01"
setPINA 0x07
continue 5
expectPORTC 0x01
checkResult

echo four 1's means there are no free parking\n
echo PART 3 UPDATE\n
echo if full set PC7 to 1\n
test "PINA: 0x0F => PORTC: 0x80"
setPINA 0x0F
continue 5
expectPORTC 0x80
checkResult
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
