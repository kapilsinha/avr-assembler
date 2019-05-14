cpi r16,$42 ; Compare r16 to $42
brne error ; Branch if r16 ⇔ $42
jmp ok ; Unconditional branch
error: add r16,r17 ; Add r17 to r16
inc r16 ; Increment r16
ok: nop ; Destination for rjmp (do nothing)


