#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ptrace.h>

int		auth(char login[32], int serial) {
	int		pid;
	int		i;
	int		len;
	int		new;

	login[strcspn(login, "\n")] = '\0';
	len = strnlen(login, 32);
	if (len < 6) {
		return 1;
	} else {
		pid = ptrace(0,0,1,0); //ptrace(PTRACE_TRACEME);
		if (pid == -1) {
			puts("\x1b[32m.---------------------------.");
			puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
			puts("\x1b[32m\'---------------------------\'");
			return 1;
		} else {
			new = (login[3] ^ 0x1337) + 0x5eeded;
			i = 0;
			while (i < len) {
				if (login[i] < ' ') {
					return 1;
				}
				new = new + (login[i] ^ new) % 0x539;
				i++;
			}	
			if (serial == new) {
				return 0;
			}
		}
	}
	return 1;
}

int		main(void) {
	char	login[32];
	int		serial;

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(&login, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%d", &serial);
	if (auth(login, serial) == 0) {
		puts("Authenticated!");
		system("/bin/sh");
	}
	return 0;
}
