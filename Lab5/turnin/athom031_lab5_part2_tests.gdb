echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x03 => PORTC: 0x00"
setPINA 0x03
continue 2
expectPORTC 0x00
checkResult
echo \n

#decrement at 0 shouldnt do anything
test "PINA: 0x03, 0x01 => PORTC: 0x00"
setPINA 0x03
continue 2
setPINA 0x01
continue 2
expectPORTC 0x00
checkResult
echo \n

#increment till 9 and keep incrementing should be 9
test "PINA: 0x03,0x02...  => PORTC: 0x09"
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
expectPORTC 0x09
checkResult
echo \n

test "PINA: 0x03, 0x02, 0x03, 0x01 => PORTC: 0x00"
setPINA 0x00
continue 2
setPINA 0x03
continue 2
setPINA 0x02
continue 2
setPINA 0x03
continue 2
setPINA 0x01
continue 2
expectPORTC 0x00
checkResult
echo \n

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
