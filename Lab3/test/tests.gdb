# Test file for "Lab3_bitManip"


echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x00 => PORTB: 0x00 PORTC: 0x00"
setPINA 0x00
continue 5
expectPORTB 0x00
expectPORTC 0x00
checkResult

test "PINA: 0xFF => PORTB: 0x0F PORTC: 0xF0"
setPINA 0xFF
continue 5
expectPORTB 0x0F
expectPORTC 0xF0
checkResult

test "PINA: 0xAB => PORTB: 0x0A PORTC: 0xB0"
setPINA 0xAB
continue 5
expectPORTB 0x0A
expectPORTC 0xB0
checkResult


test "PINA: 0x29 => PORTB: 0x02 PORTC: 0x90"
setPINA 0x29
continue 5
expectPORTB 0x02
expectPORTC 0x90
checkResult
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
