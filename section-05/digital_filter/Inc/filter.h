#ifndef filter_h
#define filter_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	bool full;
	int len;
	int arr[];
} buffer;

float kernel[1024] = {1 / 2};

int add_to_buffer(buffer *buf, int val);

int clear_buffer(buffer *buf);

int *get_coefficients(buffer *buf);

int generate_delta();

int generate_sine();

int convolve(buffer *buf);

#endif