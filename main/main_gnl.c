#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void run_fd(const char *file)
{
    char    *line;
    int     fd;
    
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("Error open file !\n");
        return ;
    }
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}

int main(int argc, char **argv)
{
    int i;

    if (argc != 2)
        return (write(1, "File Needed !\n", 14));
    i = 1;
    while (i < argc)
    {
        run_fd(argv[i]);
        i++;
    }
    return (0);
}
