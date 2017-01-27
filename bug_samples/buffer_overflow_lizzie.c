/* -*- compile-command: "gcc -fsanitize=address asan.c -o asan" -*- */
#include <stddef.h>

int main (int argc, char **argv)
{
	char buff[10] = {0};
	for (size_t i = 0; i <= 10; i++) {
		buff[i] = 0xff;
	}
	return 0;
}
