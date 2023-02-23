#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char buffer[1024];
    getcwd(buffer, 1024);
    printf("getcwd ==%s\n------------------------------------------\n", buffer);
    int fd = open ("output.c", O_WRONLY);
    printf("isatty == %d" , isatty(fd));
    puts("-----------------------------------------------");
    printf("ttyname == %s", ttyname(fd));
}
