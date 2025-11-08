#ifndef filter_h
#define filter_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>

#define BUFFER_SIZE 256
#define KERNEL_SIZE 10
#define PI 3.1415926f
#define DIGITAL_FREQ 0.1f
typedef struct
{
	bool full;
	uint16_t len;
	float data[BUFFER_SIZE];
} buffer;

extern float kernel[KERNEL_SIZE];

void init_buf(buffer *buf);

void add_to_buffer(buffer *buf, float val);

int clear_buffer(buffer *buf);

int *get_coefficients(buffer *buf);

void generate_delta(buffer *buf);

void generate_sine(buffer *buf);

void convolve(buffer *buf, int *kernel, uint32_t kern_len, float *output);

float process(buffer *buf);

#endif