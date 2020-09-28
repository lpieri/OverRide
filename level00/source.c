#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int pass;

	puts("***********************************");
	puts("*  \t  -Level00 -\t\t*");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &pass);
	if (pass != 5276) {
		puts("\nInvalid Password!");
	} else {
		puts("\nAuthenticated!");
		system("/bin/sh");
	}
	return (0);
}
