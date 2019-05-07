# avr-assembler
This is an implementation of a stripped down AVR assembler

## Supported Features
* Large set of AVR instructions, consisting of
    * Arithmetic and Logical Unit (ALU) instructions
        * add, sub, and, or, eor, inc, dec, tst, clr, mul
    * Branch instructions
        * rjmp, jmp, rcall, call, ret, reti, cp, cpi, breq, brne, brge, brlt
    * Data Transfer instructions
        * mov, ldi, lds, ld, sts, st, in, out, push, pop
    * Bit and Bit-Test instructions
        * lsl, lsr, asr, nop
* Requires whitespace or comma separation between instructions and operands
* No
    * Expressions
    * Directives
    * Preprocessor directives
    * Multi-line comments / continuations

## References
<https://www.microchip.com/webdoc/avrassembler/> <br>
<http://academy.cba.mit.edu/classes/embedded_programming/doc1022.pdf> <br>
<http://web.csulb.edu/~hill/ee346/Lectures/16%20AVR%20Instruction%20Encoding.pdf>
