

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "../libft/libft.h"
int main(int ac, char **av, char **ev)
{

	int fdd[2];
	pipe(fdd);
	printf("%d , %d\n", fdd[0], fdd[1]);
	int id = fork();
	if(id == 0)
	{

		close(fdd[0]);
		dup2(fdd[1], 1);
		char **retsplit;
		while(*ev)
		{
			if(!strncmp(*ev, "PATH", 4))
			{
				retsplit = ft_split(*ev, '=');
				retsplit = ft_split(retsplit[1], ':');
			}
			ev++;
		}

		while(*retsplit)
		{
			*retsplit = ft_strjoin(*retsplit,av[2]);
				// puts(*retsplit);
			if(access(*retsplit, F_OK) != -1)
			{
				retsplit[1] = strdup(av[1]);
				retsplit[2] = NULL;
				execve(retsplit[0], retsplit, ev);
			}
			retsplit++;
		}
		char str[10];
		close(fdd[1]);
	}
	else
	{
		close(fdd[1]);
		wait(NULL);
		char str[10];
		int nb;
		dup2(fdd[0], 0);
		char *args[] = {"grep", "NAME", 0};
		execve("/usr/bin/grep", args, ev);
	}
}