#include <stdio.h>
#include <string.h>

char a_user_name[256];

int verify_user_name(void) {
	puts("verifying username...\n");
	return strncmp("dat_wil", a_user_name, 7);
}

int verify_user_pass(char *pass) {
	return strncmp("admin", pass, 5);
}

int main(void) {
	int ret;
	char pass[64];
	int pass_ok;

	bzero(&(pass[0]), 64);
	pass_ok = 0;
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 256, (FILE*)stdin);
	if (verify_user_name() == 0) {
		puts("Enter Password: ");
		fgets(pass, 100, (FILE*)stdin);
		pass_ok = verify_user_pass(pass);
		if (pass_ok == 0 || pass_ok != 0) {
			puts("nope, incorrect password...\n");
			ret = 1;
		} else {
			ret = 0;
		}
	} else {
		puts("nope, incorrect username...\n");
		ret = 1;
	}
	return ret;
}
