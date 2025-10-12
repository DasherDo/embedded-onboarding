.syntax unified
.thumb
.global HAL_GPIO_WritePin
.type HAL_GPIO_WritePin, %function

HAL_GPIO_WritePin:

	push {r4, lr}
	movs r4, r1		// GPIO_Pin

	cmp r2, #0
	beq reset

	str r4, [r0, #0x18]
	b exit


reset:
	lsls r4, r4, #8
	lsls r4, r4, #8
	str r4, [r0, #0x18]

exit:
	pop {r4, pc}