#include "main.h"
#include "filter.h"

int main()
{
	// Create empty buffer
	buffer input;

	init_buf(&input);

	float output[KERNEL_SIZE + BUFFER_SIZE - 1];

	// Initialize output to all 0's, garbage information will corrupt convolution
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
	printf("\n\n\n");

	// Reinitialize buffer and add data points one by one
	init_buf(&input);
	// Initialize output to all 0's, garbage information will corrupt convolution
	for (uint16_t i = 0; i < KERNEL_SIZE + BUFFER_SIZE - 1; i++)
	{
		output[i] = 0.0f;
	}

	// Only one item in buffer, so convolution will not be valid
	add_to_buffer(&input, 1.0f);

	// Convolve returns a 0 if the input is not the full length
	while (!convolve(&input, output))
	{
		add_to_buffer(&input, 0.0f);
	}

	// Once convolution is successfully performed
	for (uint16_t i = 0; i < KERNEL_SIZE + BUFFER_SIZE - 1; i++)
	{
		printf("%.4f, ", output[i]);
	}
	printf("\n\n\n");

	// Reinitialize buffer to test sin input
	init_buf(&input);
	uint16_t index = 0;
	while (!convolve(&input, output))
	{
		add_to_buffer(&input, sinf(2 * PI * DIGITAL_FREQ * index));
		index++;
	}

	// Once convolution is successfully performed
	for (uint16_t i = 0; i < KERNEL_SIZE + BUFFER_SIZE - 1; i++)
	{
		printf("%.4f, ", output[i]);
	}

	return 0;
}