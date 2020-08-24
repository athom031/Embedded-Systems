# Test file for "Lab3_bitManip"


echo ======================================================\n
echo Running all tests..."\n\n

# test first whether an empty seat produces any output
test "PIND: 0x00, PINB:0x00 => PORTB: 0x01"
setPIND 0x00
setPINB 0x00
continue 5
expectPORTB 0x00
checkResult

# test if a bit in PINB causes output (shouldn't)
test "PIND: 0x00, PINB:0x01 => PORTB: 0x01"
setPIND 0x00
setPINB 0x01
continue 5
expectPORTB 0x00
checkResult

# test a weight that would state carseat is disabled
# with B bit
test "PIND: 0x03, PINB:0x00 => PORTB: 0x01"
setPIND 0x03
setPINB 0x00
continue 5
expectPORTB 0x04
checkResult

test "PIND: 0x03, PINB:0x01 => PORTB: 0x04"
setPIND 0x03
setPINB 0x01
continue 5
expectPORTB 0x04
checkResult

# test with a weight of 5
test "PIND: 0x02, PINB:0x01 => PORTB: 0x00"
setPIND 0x02
setPINB 0x01
continue 5
expectPORTB 0x00
checkResult

# test with a weight of 70
test "PIND: 0x23, PINB:0x00 => PORTB: 0x02"
setPIND 0x23
setPINB 0x00
continue 5
expectPORTB 0x02
checkResult

#test with max weight 
test "PIND: 0xFF, PINB:0x01 => PORTB: 0x02"
setPIND 0xFF
setPINB 0x01
continue 5
expectPORTB 0x02
checkResult






# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
