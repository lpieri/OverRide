#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	log_wrapper(FILE *fd_log, char *str, char *fd_backup) {
	char	buffer[264];

	strcpy(buffer, str);
	snprintf(buffer + strlen(buffer), 264 - strlen(buffer), fd_backup);
	buffer[strcspn(buffer, "\n")] = '\0';
	fprintf(fd_log, "LOG: %s\n", buffer);
	return ;
}

int		main(int ac, char **av) {
	FILE	*fd_log;
	FILE	*fd_backup;
	int		fd_new;
	char	c;
	char	backup_file[100];

	if (ac != 2)
		printf("Usage: %s filename\n", av[0]);
	fd_log = fopen("./backups/.log", "w");
	if (fd_log == NULL) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(fd_log, "Starting back up: ", av[1]);
	fd_backup = fopen(av[1], "r");
	if (fd_backup == NULL) {
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(1);
	}
	strcpy(backup_file, "./backups");
	strncat(backup_file, av[1], 99 - strlen(backup_file));
	fd_new = open(backup_file, 193, 432);
	if (fd_new < 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups", av[1]);
		exit(1);
	}
	while((c = fgetc(fd_backup)) != -1) {
		write(fd_new, c, 1);
	}
	log_wrapper(fd_log, "Finished back up ", av[1]);
	fclose(fd_backup);
	close(fd_new);
	return 0;
}
