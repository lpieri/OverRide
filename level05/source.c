#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		main(void) {
	char	buffer[100];
	int		i;

	i = 0;
	fgets(&buffer, 100, stdin);
	while (i < strlen(buffer)) {
		if (buffer[i] > '@' && buffer[i] < '[')
			buffer[i] = buffer[i] ^ 32;
		i++;
	}
	printf(buffer);
	exit(0);
	return 0;
}
