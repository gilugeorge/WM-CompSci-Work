;Eric Shih
;small.asm
;
;This program searches through an array
;and finds the smallest value and stores
;it in 'smallest' and R0.

	.ORIG x3000
	
;load in the array and initialize values
;R0 is the smallest number, R1 is the counter
;R2 is the current value being compared, R3 and R5
;are temp registers , and R4 is the array.
	And R0, R0, #0
	And R2, R2, #0	
	Ld R1, LIST_SIZE
	LEA R4, values
	LDR R0, R4, #0		;Load initial values from index 0

;Begin the sequence of checks. This traverses
;through the entire array while checking each
;value with the current smallest array.
check	Add R4, R4, #1
	LDR R2, R4, #0		;load next value
	Add R1, R1, #-1
	BRz end			;when the array has been traversed

	Not R3, R0		;make negative to prep for
	Add R3, R3, #1		;comparison

	Add R5, R2, R3		;Send to replace R0 with new value
	BRzp check		;or back up the loop.
	BR  less

less	And R0, R0, #0		;initialize back to zero
	Add R0, R2, #0		;add new smallest value
	BR  check

end	HALT

;
;Storage for array, array size, and blkw.
;
values	  .fill -1
	  .fill 5
	  .fill 6
	  .fill 88
	  .fill 9
	  .fill 10
	  .fill 4
	  .fill 0
	  .fill 11
	  .fill 9
	  .fill 7
	  .fill 15
	  .fill 22
	  .fill 19
	  .fill 11
	  .fill 17
	  .fill 11
	
list	  .blkw 50
LIST_SIZE .fill 17


	.END