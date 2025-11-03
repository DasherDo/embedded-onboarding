#ifndef filter_h
#define filter_h

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	bool full;
	int len;
	int arr[];
} buffer;

int add_to_buffer(buffer *buf, int val);

#endif