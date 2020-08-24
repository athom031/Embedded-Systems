# Test file for "Lab2_introToAVR"



echo ======================================================\n
echo Running all tests..."\n\n

#check default inputs

test "PINA: 0x00 => PORTB: 0x00"
setPINA 0x00
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0x01 => PORTB: 0x00"
setPINA 0x01
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0x02 => PORTB: 0x01"
setPINA 0x02
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0x03 => PORTB: 0x00"
setPINA 0x03
continue 5
expectPORTB 0x00
checkResult


#check if trivial values affect results
test "PINA: 0xF3 => PORTB: 0x00"
setPINA 0x03
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0xFE => PORTB: 0x01"
setPINA 0xFE
continue 5
expectPORTB 0x01
checkResult
 
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
