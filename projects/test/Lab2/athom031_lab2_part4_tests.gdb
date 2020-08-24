# Test file for "Lab2_introToAVR"

echo ======================================================\n
echo Running all tests..."\n\n

echo check if our code sets up default input and output\n

test "PINA: 0x00, PINB: 0x00, PINC: 0x00 => PORTD: 0x00"
setPINA 0x00
setPINB 0x00
setPINC 0x00
continue 5
expectPORTD 0x00
checkResult

echo test overweight weight total\n

test "PINA: 0x3C, PINB: 0x3C, PINC: 0x3C => PORTD: 0xD1"
setPINA 0x3C
setPINB 0x3C
setPINC 0x3C
continue 5
expectPORTD 0xB5
checkResult

echo test desired weight distribution set\n

test "PINA: 0x28, PINB: 0x3C, PINC: 0x28 => PORTD: 0xD1"
setPINA 0x28
setPINB 0x3C
setPINC 0x28
continue 5
expectPORTD 0x8C
checkResult

echo test unbalanced carts\n

test "PINA: 0x64, PINB: 0x0A, PINC: 0x0A => PORTD: 0xD1"
setPINA 0x64
setPINB 0x0A
setPINC 0x0A
continue 5
expectPORTD 0x7A
checkResult

test "PINA: 0x0A, PINB: 0x0A, PINC: 0x64 => PORTD: 0xD1"
setPINA 0x0A
setPINB 0x0A
setPINC 0x64
continue 5
expectPORTD 0x7A
checkResult

echo test whether the within 3 messes with mask\n

test "PINA: 0x35, PINB: 0x20, PINC: 0x64 => PORTD: 0xD1"
setPINA 0x35
setPINB 0x20
setPINC 0x16
continue 5
expectPORTD 0x68
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
