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

void init_buf(buffer *buf)
{
	buf->full = false;
	buf->len = 0;
	for (uint16_t i = 0; i < BUFFER_SIZE; i++)
	{
		buf->data[i] = 0.0f;
	}
}

void add_to_buffer(buffer *buf, float val)
{
	// FIFO, shift all data left
	for (uint16_t i = 0; i < BUFFER_SIZE - 1; i++)
	{
		buf->data[i] = buf->data[i + 1];
	}

	buf->data[BUFFER_SIZE - 1] = val;

	if (buf->len < BUFFER_SIZE)
	{
		buf->len++;
	}

	if (buf->len == BUFFER_SIZE)
	{
		buf->full = true;
	}
}

void generate_delta(buffer *buf)
{
	// Impulse
	buf->data[0] = 1.0f;
}

void generate_sine(buffer *buf)
{
	for (uint16_t i = 0; i < BUFFER_SIZE; i++)
	{
		buf->data[i] = sinf(2 * PI * DIGITAL_FREQ * i);
	}
}
