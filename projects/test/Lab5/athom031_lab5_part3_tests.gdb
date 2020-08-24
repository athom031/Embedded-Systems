echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x01 => PORTB: 0x00"
setPINA 0x01
continue 2
expectPORTB 0x00
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x15"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x15
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x2A"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x2A
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x03"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x03
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x30"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x30
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x0C"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x0C
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x3F"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x3F
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x00"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x00
checkResult
echo \n

test "PINA: 0x00, 0x01 => PORTB: 0x15"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x15
checkResult
echo \n

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
