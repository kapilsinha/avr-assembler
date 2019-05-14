// https://embarc.org/man-pages/as/AVR-Pseudo-Instructions.html#AVR-Pseudo-Instructions

push    r24				; 0:   8f 93
in      r24, 0x3f 		; 2:   8f b7           
push    r24				; 4:   8f 93           
lds     r24, 0x0060     ; 6:   80 91 60 00     0x800060 <var>
inc     r24 			; a:   83 95           
sts     0x0060, r24     ; c:   80 93 60 00      0x800060 <var> 
pop     r24 			; 10:   8f 91           
out     0x3f, r24 		; 12:   8f bf           
pop     r24 			; 14:   8f 91           
reti 					; 16:   18 95           
