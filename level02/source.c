#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(void) {
	size_t ret;
	char password[112];
	char pass[48];
	char username[96];
	FILE* fd;

	bzero(&(username[0]), 96);
	bzero(&(pass[0]), 48);
	bzero(&(password[0]), 112);
	fd = NULL;
	fd = fopen("/home/users/level03/.pass", "r");
	if (fd == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	ret = fread(pass, 1, 41, fd);
	*(pass + strcspn(pass, "\n")) = '\0';
	if (ret != 41) {
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}
	fclose(fd);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(username, 100, stdin);
	*(username + strcspn(username, "\n")) = '\0';
	printf("--[ Password: ");
	fgets(password, 100, stdin);
	*(password + strcspn(password, "\n")) = '\0';
	puts("*****************************************");
	if (strncmp(pass, password, 41) == 0) {
		printf("Grettings, %s!\n", username);
		system("/bin/sh");
		return 0;
	}
	printf(username);
	puts(" does not have access!");
	exit(1);
}
