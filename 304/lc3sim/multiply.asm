;Eric Shih
;multiply.asm
;
;This program mulitiplies the value in
;R0 by the value in R1 and stores the
;answer in R2 (R0*R1=R2).
;*note* I wrote for all cases
;before I knew that we only had to positives.

;
;Initialization
;
	.ORIG 	x3000
	AND	R2, R2, #0 	;set answer to 0

;
;Check whether R0 is positive or negative
;
	ADD	R0, R0, #0	;load r0 to branch check
	BRp	r0pos
	BRn	r0neg
	BRz	r0zero

;when R0 is positive, decide on R1
r0pos	ADD	R1, R1, #0
	BRp	pp
	BRn	pn2
	BRz	r1zero
;when R0 is negative, decide on R1
r0neg	ADD	R1, R1, #0
	BRp	pn1
	BRn	nn
	BRz	r1zero
;when either is zero 
r0zero
r1zero	BR	end


;
;When both values are positive
;
pp
repeat1	ADD	R2, R2, R0	;R0 + R0 = R2
	ADD	R1, R1, #-1	;decrement R1
	BRp	repeat1		;loop up to repeat
	BR	end

;
;R0 is negative, R1 is postive
;
pn1	NOT	R0, R0		;Make R0 positive
	ADD	R0, R0, #1
repeat2	ADD	R2, R2, R0
	ADD	R1, R1 #-1	;Decrement R1
	BRp	repeat2

	NOT	R2, R2		;Make the result negative
	ADD	R2, R2, #1
	BR	end
	
;
;R0 is positive, R1 is negative
;
pn2	NOT	R1, R1		;Make R1 positive
	ADD	R1, R1, #1
repeat3	ADD	R2, R2, R0
	ADD 	R1, R1, #-1
	BRp	repeat3

	NOT	R2, R2		;Make result negative
	ADD	R2, R2, #1
	BR	end
	
;
;When both values are negative
;
nn	NOT	R0, R0		;Make both positive
	NOT	R1, R1
	ADD	R0, R0, #1
	ADD	R1, R1, #1
repeat4	ADD	R2, R2, R0	;Add R0 to R2
	ADD	R1, R1, #-1	;Decrement R1
	BRp	repeat4
	BR	end
	
	
end
	HALT
	.END