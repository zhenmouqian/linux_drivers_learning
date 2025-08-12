#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        printf("file %s open fail\n", argv[1]);
        return -1;
    }
    int writeval = atoi(argv[2]);
    int ret = write(fd, &writeval, 1);
    if (ret < 0)
    {
        printf("write fail\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}