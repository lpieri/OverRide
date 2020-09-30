#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <strings.h>

int main(void) {
	char	buffer[128];
	int		pid;
	int		var1;
	int		var2;

	bzero(&(buffer[0]), 128);
	pid = fork();
	var1 = 0;
	var2 = 0;
	if (pid == 0) {
		prctl(1, 1);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buffer);
		return 0;
	} else {
		while (var2 != 11) {
			wait(&var1);
			if ((var1 & 127) == 0 || ((var1 & 127) + 1) / 2 > 0) {
				puts("child is exiting...");
				return 0;
			}
			var2 = ptrace(PTRACE_PEEKUSER, pid, 44, 0);
		}
		puts("no exec() for you");
		kill(pid, 9);
	}
	return 0;
}
