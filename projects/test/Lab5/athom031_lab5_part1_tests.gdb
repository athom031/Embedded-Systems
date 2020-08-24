echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x00 => PORTC: 0x3F"
setPINA 0x00
continue 2
expectPORTC 0x3F
checkResult
echo \n

test "PINA: 0x01 => PORTC: 0x3F"
setPINA 0x01
continue 2
expectPORTC 0x3F
checkResult
echo \n

test "PINA: 0x02 => PORTC: 0x3F"
setPINA 0x02
continue 2
expectPORTC 0x3F
checkResult
echo \n

test "PINA: 0x03 => PORTC: 0x3E"
setPINA 0x03
continue 2
expectPORTC 0x3E
checkResult
echo \n

test "PINA: 0x04 => PORTC: 0x3E"
setPINA 0x04
continue 2
expectPORTC 0x3E
checkResult
echo \n

test "PINA: 0x05 => PORTC: 0x3E"
setPINA 0x05
continue 2
expectPORTC 0x3E
checkResult
echo \n

test "PINA: 0x06 => PORTC: 0x3C"
setPINA 0x06
continue 2
expectPORTC 0x3C
checkResult
echo \n

test "PINA: 0x07 => PORTC: 0x3C"
setPINA 0x07
continue 2
expectPORTC 0x3C
checkResult
echo \n

test "PINA: 0x08 => PORTC: 0x3C"
setPINA 0x08
continue 2
expectPORTC 0x3C
checkResult
echo \n

test "PINA: 0x09 => PORTC: 0x38"
setPINA 0x09
continue 2
expectPORTC 0x38
checkResult
echo \n

test "PINA: 0x0A => PORTC: 0x38"
setPINA 0x0A
continue 2
expectPORTC 0x38
checkResult
echo \n

test "PINA: 0x0B => PORTC: 0x70"
setPINA 0x0B
continue 2
expectPORTC 0x70
checkResult
echo \n

test "PINA: 0x0C => PORTC: 0x70"
setPINA 0x0C
continue 2
expectPORTC 0x70
checkResult
echo \n

test "PINA: 0x0D => PORTC: 0x60"
setPINA 0x0D
continue 2
expectPORTC 0x60
checkResult
echo \n

test "PINA: 0x0E => PORTC: 0x60"
setPINA 0x0E
continue 2
expectPORTC 0x60
checkResult
echo \n

test "PINA: 0x0F => PORTC: 0x40"
setPINA 0x0F
continue 2
expectPORTC 0x40
checkResult
echo \n


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
