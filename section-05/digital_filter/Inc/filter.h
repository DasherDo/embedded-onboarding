#ifndef filter_h
#define filter_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct
{
	bool full;
	int len;
	float *data;
} buffer;

float kernel[1024] = {1 / 2};

int add_to_buffer(buffer *buf, int val);

int clear_buffer(buffer *buf);

int *get_coefficients(buffer *buf);

int generate_delta();

int generate_sine();

int convolve(buffer *buf, int *kernel, uint32_t kern_len, float *output);

#endif