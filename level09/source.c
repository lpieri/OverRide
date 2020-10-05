#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

typedef struct	s_msg {
	char	msg[140];
	char	username[40];
	int		len;
}				t_msg;

void	secret_backdoor(void) {
	char	cmd[128];

	fgets(cmd, 128, stdin);
	system(cmd);
	return ;
}

void	set_msg(t_msg *msg) {
	char	message[1024];

	bzero(&(message[0]), 1024);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(message, 1024, stdin);
	strncpy(msg->msg, message, msg->len);
	return ;
}

void	set_username(t_msg *msg) {
	char	user[128];
	int		i;

	i = 0;
	bzero(&(user[0]), 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(user, 128, stdin);
	while (i <= 40 && user[i] != '\0') {
		msg->username[i] = user[i];
		i++;
	}
	printf(">: Welcome, %s", msg->username);
	return ;
}

void	handle_msg(void) {
	t_msg	msg;

	bzero(&(msg.username[0]), 40);
	msg.len = 140;
	set_username(&msg);
	set_msg(&msg);
	puts(">: Msg sent!");
	return ;
}

int		main(void) {
	puts("--------------------------------------------\n");
	puts("|   ~Welcome to l33t-m$n ~    v1337        |\n");
	puts("--------------------------------------------\n");
	handle_msg();
	return 0;
}
