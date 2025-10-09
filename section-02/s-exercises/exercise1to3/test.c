#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int main()
{
	uint32_t pins = 0b00000000001000000000000000000001;

	int position = 0;
	while ((pins >> position) != 0x00u)
	{
		printf("%d", pins >> position);
		position++;
	}
	printf("Final Position: %d", position);
	printf("Final pins: %d", pins >> position);
}