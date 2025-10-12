.syntax unified
.thumb
.global HAL_GPIO_Init
.type HAL_GPIO_Init, %function

HAL_GPIO_Init:
	
	push {r3-r7, lr}
	movs r4, #0	// Keep track of cur pin

loop:
	cmp r4, #16	// While cur pin is < 16
	bge exit_loop

	ldr r5, [r1, #0]	// GPIO_Init->Pin
	movs r6, #1
	lsls r6, r6, r4		// 0b1 << cur_pin
	tst r5, r6			// Test if pin is selected to init
	beq skip

	// Simplified init, only MODER, OSPEEDR, OTYPER configuration
	// MODER, each pin 2 bits

	ldr r7, [r0, #0]	// MODER at GPIOx offset 0x00u
	movs r5, #3
	lsls r3, r4, #1	
	lsls r5, r5, r3
	mvns r5, r5
	ands r7, r7, r5		// Clear bits

	ldr r5, [r1, #0x04]	// GPIO_Init->Mode
//	movs r6, #2
//	ands r5, r5, r6
	lsls r5, r5, r3
	orrs r7, r7, r5
	str r7, [r0, #0]

	// OTYPER, each pin 1 bit
	ldr r7, [r0, #0x04]
	movs r5, #1
	lsls r5, r4
	mvns r5, r5
	ands r7, r7, r5

	ldr r5, [r1, #0x04]	
	lsrs r5, r5, #4
	movs r6, #1
	ands r5, r6
	lsls r5, r5, r4
	orrs r7, r7, r5
	str r7, [r0, #0x04]

	// OSPEEDR, each pin is 2 bits
	ldr r7, [r0, #0x08]
	movs r5, #3
	lsls r5, r5, r3
	mvns r5, r5
	ands r7, r7, r5

	ldr r5, [r1, #0x0C]
	lsrs r5, r5, r3
	orrs r7, r7, r5
	str r7, [r0, #0x08]

	// PUPDR
	ldr r7, [r0, #0x0C]
	movs r5, #3
	lsls r5, r5, r3
	mvns r5, r5
	ands r7, r7, r5

	ldr r5, [r1, #0x08]
	lsls r5, r5, r3
	orrs r7, r7, r5
	str r7,[r0, #0x0C]

	// EXTI



skip:
	adds r4, r4, #1
	b loop

exit_loop:
	pop {r3-r7, pc}

