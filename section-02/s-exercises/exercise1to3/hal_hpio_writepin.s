.thumb
.global HAL_GPIO_WritePin
.type HAL_GPIO_WritePin, %function

HAL_GPIO_WritePin:

	push {r4, lr}
	ldr r4, r1	// GPIO_Pin

	cmp r2, #0
	lsleq r4, r4, #16	// If PinState == 0 (GPIO_PIN_RESET), shift GPIO_Pin to left by 16
	str r4, [r0, #0x18]

	pop {r4, pc}