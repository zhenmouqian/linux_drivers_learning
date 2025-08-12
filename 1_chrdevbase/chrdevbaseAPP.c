#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    char readbuf[100];
    int ret = 0;

    int fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        printf("open file %s fail\r\n", argv[1]);
        return 1;
    }

    if (atoi(argv[2]) == 1)
    {
        ret = read(fd, readbuf, 100);
        if (ret < 0)
        {
            printf("read file %s fail!\r\n", argv[1]);
            return 1;
        }
        else
        {
            printf("read data %s!\r\n", readbuf);
            return 0;
        }
    }
    if (atoi(argv[2]) == 2 && argc == 4)
    {
        ret = write(fd, argv[3], 100);
        if (ret < 0)
        {
            printf("write file %s fail!\r\n", argv[1]);
            return 1;
        }
    }

    ret = close(fd);
    if (ret < 0)
    {
        printf("close file %s fail\r\n", argv[1]);
        return 1;
    }
    return 0;
}