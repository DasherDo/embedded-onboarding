#include "filter.h"

float kernel[KERNEL_SIZE] = {1.0f / 8.0f, 1.0f / 8.0f, 1.0f / 8.0f, 1.0f / 8.0f, 1.0f / 8.0f, 1.0f / 8.0f, 1.0f / 8.0f, 1.0f / 8.0f};

uint16_t convolve(buffer *input, float *output)
{
	if (!input->full)
	{
		return 0;
	}
	uint16_t out_len = input->len + KERNEL_SIZE - 1;
	for (uint16_t i = 0; i < out_len; i++)
	{
		output[i] = 0.0f;
	}

	for (uint16_t i = 0; i < input->len; i++)
	{
		for (uint16_t j = 0; j < KERNEL_SIZE; j++)
		{
			output[i + j] += input->data[i] * kernel[KERNEL_SIZE - 1 - j];
		}
	}
	return 1;
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
	buf->len = BUFFER_SIZE;
	buf->full = true;
}

void generate_sine(buffer *buf)
{
	for (uint16_t i = 0; i < BUFFER_SIZE; i++)
	{
		buf->data[i] = sinf(2 * PI * DIGITAL_FREQ * i);
	}
}
