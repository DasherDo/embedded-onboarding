.syntax unified
.thumb
.global HAL_GPIO_TogglePin
.type HAL_GPIO_TogglePin, %function

HAL_GPIO_TogglePin:
	push {r4 - r6, lr}

	ldr r4, [r0, #0x18]
	cpy r6, r1
	ands r6, r4
	lsls r5, r5, #8
	lsls r5, r5, #8	// reset_pins

	mvns r6, r4
	ands r6, r6, r1

	orrs r6, r6, r5
	str r6, [r0, #0x18]

	pop {r4 - r6, pc}