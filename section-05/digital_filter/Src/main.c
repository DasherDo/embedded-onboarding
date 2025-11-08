#include "main.h"
#include "filter.h"

int main()
{
	// Create empty buffer
	buffer input;

	init_buf(&input);

	float output[KERNEL_SIZE + BUFFER_SIZE - 1];

	for (uint16_t i = 0; i < KERNEL_SIZE + BUFFER_SIZE - 1; i++)
	{
		output[i] = 0.0f;
	}

	// Set the input to an impulse
	generate_delta(&input);

	convolve(&input, output);
	for (uint16_t i = 0; i < KERNEL_SIZE + BUFFER_SIZE - 1; i++)
	{
		printf("%.4f, ", output[i]);
	}
	return 0;
}