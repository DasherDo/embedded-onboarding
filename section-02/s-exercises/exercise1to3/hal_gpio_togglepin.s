.thumb
.global HAL_GPIO_TogglePin
.type HAL_GPIO_TogglePin, %function

HAL_GPIO_TogglePin:
	push {r4 - r6, lr}

	ldr r4, [r0, #0x14]
	and r5, r4, r1
	lsl r5, r5, 16	// reset_pins

	mvn r6, r4
	and r6, r6, r1

	orr r6, r6, r5
	str r6, [r0, #0x14]

	pop {r4 - r6, pc}