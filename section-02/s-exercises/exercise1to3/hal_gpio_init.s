.thumb
.global HAL_GPIO_Init
.type HAL_GPIO_Init, %function

HAL_GPIO_Init:
	
	push {r4-r7, lr}
	movs r4, #0	// Keep track of cur pin

loop:
	cmp r4, #16	// While cur pin is < 16
	bge exit_loop

	ldr r5, [r1, #0]	// GPIO_Init->Pin
	movs r6, #1
	lsl r6, r4			// 0b1 << cur_pin
	tst r5, r6			// Test if pin is selected to init
	beq skip

	// Simplified init, only MODER, OSPEEDR, OTYPER configuration
	// MODER, each pin 2 bits

	ldr r7, [r0, #0]	// MODER at GPIOx offset 0x00u
	movs r5, #1
	lsl	r5, r4, #1
	mvn r5, r5
	and r7, r7, r5		// Clear bits

	ldr r5, [r1, #0x04]	// GPIO_Init->Mode
	and r5, r5, #0x02		
	lsl r5, r5, r4, #1
	orr r7, r7, r5
	str r7, [r0, #0]

	// OTYPER, each pin 1 bit
	ldr r7, [r0, #0x04]
	movs r5, #1
	lsl r5, r4
	mvn r5, r5
	and r7, r7, r5

	ldr r5, [r1, #0x04]	
	lsr r5, r5, #4
	and r5, r5, #0x01
	lsl r5, r5, r4
	orr r7, r7, r5
	str r7, [r0, #0x04]

	// OSPEEDR, each pin is 2 bits
	ldr r7, [r0, #0x08]
	movs r5, #0x02
	lsl r5, r5, r4, #1
	mvn r5, r5
	and r7, r7, r5

	ldr r5, [r1, #0x0C]
	lsr r5, r5, r4, #1
	orr r7, r7, r5
	str r7, [r0, #0x08]



skip:
	adds r4, r4, #1
	b loop

exit_loop:
	pop {r4-r7, pc}

