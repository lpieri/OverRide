#include <stdio.h>
#include <strings.h>

void	clear_stdin(void) {
	char	c;

	c = getchar();
	while ((c = getchar()) != -1) {
		if (c == '\n')
			return ;
	}
	return ;
}

unsigned int	get_unum(void) {
	unsigned int	nb;

	nb = 0;
	fflush(stdout);
	scanf("%u", &nb);
	clear_stdin();
	return nb;
}

int		read_number(int *tab) {
	unsigned int	nb;

	printf(" Index: ");
	nb = get_unum();
	printf(" Number at data[%u] is %u\n", nb, tab[nb]);
	return 0;
}

int		store_number(int *tab) {
	unsigned int	nb;
	unsigned int	index;

	printf(" Number: ");
	nb = get_unum();
	printf(" Index: ");
	index = get_unum();
	if (index % 3 == 0 || nb >> 24 == 183) {
		puts(" *** ERROR! *** ");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! *** ");
		return 1;
	}
	tab[index] = nb;
	return 0;
}

int		main(int ac, char **av, char **env) {
	int		tab[100];
	int		ret;
	char	str[20];

	bzero(&(tab[0]), 100);
	bzero(&(str[0]), 20);
	while (*av) {
		memset(*av, 0, strlen(*av) - 1);
		(*av)++;
	}
	while (*env) {
		memset(*env, 0, strlen(*env) - 1);
		(*env)++;
	}
	puts("----------------------------------------------------\n");
	puts("  Welcome to wil\'s crappy numberstorage service!   \n");
	puts("----------------------------------------------------\n");
	puts(" Commands:                                          \n");
	puts("    store - store a number into the data storage    \n");
	puts("    read  - read a number from the data storage     \n");
	puts("    quit  - exit the program                        \n");
	puts("----------------------------------------------------\n");
	puts("    wil has reserved somestorage :>                 \n");
	puts("----------------------------------------------------\n");
	while (1) {
		printf("Input command: ");
		fgets(str, 20, stdin);
		str[strlen(str) - 2] = '\0';
		if (strncmp("store", str, 5) == 0) {
			ret = store_number(&tab);
		} else if (strncmp("read", str, 4) == 0) {
			ret = read_number(&tab);
		} else if (strncmp("quit", str, 4) == 0) {
			break ;
		}
		if (ret == 0) {
			printf(" Completed %s command successfully\n", str);
		} else {
			printf(" Failed to do %s command\n", str);
		}
		bzero(&(str[0]), 20);
	}
	return 0;
}
