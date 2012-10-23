; Eric Shih
; count.asm
;
; This program counts the number of 1's
; in R0 and stores the result in R1.

	.ORIG x3000
	
;Initialize the R1 for results.
	And R1, R1, #0		;the result counter
	And R3, R3, #0		;holds the value to be checked
	And R2, R2, #0		;Bit to be shifted for checking
	Add R2, R2, #1
	LD  R4, lastBit		;Register to determine end of loop, 2^15

;Check for correct bit
check	And R3, R0, R2		;Compares R0 with the new bit function
	BRz shift
	Add R1, R1, #1

shift	Not R3, R2		;Make R2 value negative for comparison with lastBit
	Add R3, R3, #1
	Add R5, R4, R3		;if zero, all bits checked
	Brz end	
	Add R2, R2, R2		;move to next bit
	Br  check	

end	HALT
	
;set the last bit to stop the loop
lastBit	.fill	-32768
	
	.END