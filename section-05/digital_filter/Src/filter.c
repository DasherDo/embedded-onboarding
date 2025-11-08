#include "filter.h"

void convolve(buffer *input, float *kernel, uint32_t kern_len, float *output)
{
	uint16_t out_len = input->len + kern_len - 1;
	for (uint16_t i = 0; i < out_len; i++)
	{
		output[i] = 0.0f;
	}

	for (uint16_t i = 0; i < input->len; i++)
	{
		for (uint16_t j = 0; j < kern_len; j++)
		{
			output[i + j] += input->data[i] * kernel[kern_len - 1 - j];
		}
	}
}