



#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
int main(int ac, char **av , char **env) 
{

    char *str[5] = {"/usr/bin/awk" , "{printf (\"mehdiboulhoujjat\")}"};
    execve(str[0], str, env);

}