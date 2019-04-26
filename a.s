.section	.data
prod:		.word		0
multiplier:		.word		0

.section	.text
d:		.asciz		"%d"
dn:		.asciz		"%d\n"
s0:		.asciz		"Factorial of 10 is:"

.global		main
.balign		4

main:
		push {lr}
		ldr r0, =s0
		bl printf
		bl compute10
		mov r1,r0 
		ldr r0, =dn
		bl printf
		pop {pc}


compute10:
		push {lr}
		mov r1, #1
		ldr r0, =multiplier
		str r1, [r0]
		mov r1, #1
		ldr r0, =prod
		str r1, [r0]
l0:
		ldr r0, =multiplier
		ldr r1, [r0]
		mov r2, #10
		mov r0, #1
		cmp r1, r2
		ble j0
		mov r0, #0
j0:
		mov r1, r0 
		cmp r1, #0
		beq le0
		ldr r0, =prod
		ldr r1, [r0]
		ldr r0, =multiplier
		ldr r2, [r0]
		mul r1, r1, r2
		ldr r0, =prod
		str r1, [r0]
		ldr r0, =multiplier
		ldr r1, [r0]
		mov r2, #1
		add r1, r1, r2
		ldr r0, =multiplier
		str r1, [r0]
		b l0
le0:
		ldr r0, =prod
		ldr r1, [r0]
		mov r0, r1
		pop {pc}
