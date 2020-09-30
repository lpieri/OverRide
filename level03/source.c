#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int decrypt(int nb) {
	char	str[17] = "Q}|u`sfg~sf{}|a3";
	size_t	len;
	int		i;

	len = strlen(str);
	i = 0;
	while (i < len) {
		str[i] = str[i] ^ nb;
		i++;
	}
	if (strncmp(str, "Congratulations!", 17) == 0) {
		system("/bin/sh");
	} else {
		puts("\nInvalid Password");
	}
	return 0;
}

void test(int p1, int p2) {
	int nb;

	nb = p2 - p1;
	switch(nb){
		default:
			decrypt(rand());
			break;
		case(1):
			decrypt(nb);
			break;
		case(2):
			decrypt(nb);
			break;
		case(3):
			decrypt(nb);
			break;
		case(4):
			decrypt(nb);
			break;
		case(5):
			decrypt(nb);
			break;
		case(6):
			decrypt(nb);
			break;
		case(8):
			decrypt(nb);
			break;
		case(9):
			decrypt(nb);
			break;
		case(16):
			decrypt(nb);
			break;
		case(17):
			decrypt(nb);
			break;
		case(18):
			decrypt(nb);
			break;
		case(20):
			decrypt(nb);
			break;
		case(21):
			decrypt(nb);
			break;
	}
}

int main(void) {
	int		pass;

	srand(time(NULL));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &pass);
	test(pass, 322424845);
	return 0;
}
